# C Systems Challenges

Repositório de estudos em C com foco em engenharia de sistemas, depuração e análise de problemas clássicos de baixo nível.

## Objetivo

Este material foi organizado para treinar:

- gerenciamento de memória
- leitura e análise de código legado
- identificação de bugs sutis
- uso de ferramentas de depuração
- raciocínio sobre concorrência
- validação de comportamento em tempo de execução

Os arquivos deste repositório **contêm problemas intencionais**. O objetivo é que você leia, execute, observe o comportamento, formule hipóteses e corrija por conta própria.

Este README **não traz as respostas prontas**. Ele explica o problema, como executar, o que observar e como investigar com ferramentas como `gdb` e `valgrind`.

---

## Estrutura do projeto

```text
c-systems-challenges/
├── README.md
├── Makefile
├── memory/
│   ├── memory_leak_bug.c
│   ├── double_free_bug.c
│   └── realloc_misuse_bug.c
├── concurrency/
│   ├── race_condition_bug.c
│   ├── deadlock_bug.c
│   └── shared_buffer_bug.c
└── data_structures/
    ├── linked_list_leak_bug.c
    └── linked_list_use_after_free_bug.c
```

---

## Pré-requisitos

Em ambiente Linux, instale compilador e ferramentas de análise.

### Ubuntu / Debian

```bash
apt update
apt install -y build-essential gdb valgrind
```

### Fedora

```bash
dnf install -y gcc make gdb valgrind
```

### Arch

```bash
pacman -S gcc make gdb valgrind
```

---

## Como compilar

Você pode compilar individualmente com `gcc` ou usar o `Makefile`.

### Compilando um arquivo isolado

Exemplo:

```bash
gcc -Wall -Wextra -Wpedantic -g -O0 memory/memory_leak_bug.c -o memory_leak_bug
```

Para programas com threads, lembre de incluir `-pthread`:

```bash
gcc -Wall -Wextra -Wpedantic -g -O0 -pthread concurrency/race_condition_bug.c -o race_condition_bug
```

### Usando o Makefile

```bash
make all
```

Isso gera os binários na pasta `bin/`.

### Limpando binários

```bash
make clean
```

---

## Boas práticas para estudar estes desafios

A melhor forma de usar este repositório é seguir um fluxo disciplinado:

1. Leia o código sem executar.
2. Tente prever o que ele deveria fazer.
3. Tente prever onde ele pode falhar.
4. Compile com warnings habilitados.
5. Execute normalmente.
6. Execute repetidas vezes quando houver concorrência.
7. Rode com `valgrind` quando o problema envolver memória.
8. Rode com `gdb` quando o comportamento for inconsistente ou houver crash.
9. Anote suas hipóteses antes de alterar o código.
10. Só depois faça a correção.

A ideia é treinar seu raciocínio técnico, e não apenas “consertar até funcionar”.

---

## Flags de compilação recomendadas

Use sempre:

```bash
-Wall -Wextra -Wpedantic -g -O0
```

### Por quê?

- `-Wall -Wextra -Wpedantic`: aumentam a chance de o compilador apontar problemas cedo.
- `-g`: adiciona símbolos de depuração para uso com `gdb` e `valgrind`.
- `-O0`: desabilita otimizações para facilitar a análise de comportamento.

---

## Ferramentas de análise

## 1. Valgrind

Muito útil para:

- memory leak
- uso de memória não inicializada
- leitura/escrita inválida
- uso após `free`
- `double free`

### Comando base

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/<programa>
```

### O que observar

- `definitely lost`: memória certamente vazada
- `indirectly lost`: vazamento encadeado
- `Invalid read` / `Invalid write`: acesso indevido
- `Use of uninitialised value`: valor usado sem inicialização
- stack trace das alocações e acessos inválidos

### O que anotar durante a análise

- Quem alocou a memória?
- Quem deveria liberá-la?
- O ponteiro ainda é válido no ponto de uso?
- A estrutura inteira foi desalocada ou só a cabeça?
- A lógica com `realloc` preserva o ponteiro original em caso de falha?

---

## 2. GDB

Muito útil para:

- segmentation fault
- travamento inesperado
- inspeção de ponteiros
- inspeção de threads
- análise de fluxo
- entendimento de deadlock e bloqueios

### Fluxo básico

```bash
gdb ./bin/<programa>
```

Dentro do `gdb`:

```gdb
break main
run
next
step
print variavel
bt
continue
quit
```

### Comandos especialmente úteis

- `break <linha|função>`: cria breakpoint
- `run`: executa o programa
- `next`: executa a próxima linha sem entrar em função
- `step`: entra na função
- `print <expr>`: imprime valor
- `bt`: stack trace
- `info locals`: mostra variáveis locais
- `watch <variavel>`: pausa quando o valor mudar
- `info threads`: lista threads
- `thread <id>`: troca para uma thread específica
- `x/<formato> <endereço>`: examina memória

### Exemplos úteis

Ver conteúdo de um ponteiro:

```gdb
print ptr
x/16xb ptr
```

Monitorar alteração inesperada em variável global:

```gdb
watch counter
run
```

Inspecionar threads:

```gdb
info threads
thread 2
bt
```

---

# Desafios por categoria

---

## MEMORY

### 1. `memory/memory_leak_bug.c`

#### Tipo de problema

Vazamento de memória por ausência de liberação após uso.

#### O que o programa faz

Cria mensagens dinamicamente e as imprime.

#### O que investigar

- Toda memória alocada com `malloc` tem caminho correspondente de `free`?
- A responsabilidade pela desalocação está clara?
- O padrão usado no código escala bem se esse fluxo for executado muitas vezes?

#### Como executar

```bash
./bin/memory_leak_bug
```

#### Como analisar com Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/memory_leak_bug
```

#### O que observar

- quantidade de bytes perdidos
- local da alocação
- se a perda é “definitely lost”

#### Perguntas para responder antes de corrigir

- Qual função aloca?
- Quem deveria liberar?
- Em que ponto da execução essa liberação deveria acontecer?

---

### 2. `memory/double_free_bug.c`

#### Tipo de problema

Uso após liberação e tentativa de liberar o mesmo ponteiro mais de uma vez.

#### O que o programa faz

Aloca um vetor, escreve valores, libera a memória e depois continua interagindo com ela.

#### O que investigar

- Há acesso a memória já liberada?
- O ponteiro é invalidado após `free`?
- Existe mais de uma chamada de `free` para o mesmo endereço?

#### Como executar

```bash
./bin/double_free_bug
```

#### Como analisar com Valgrind

```bash
valgrind --track-origins=yes ./bin/double_free_bug
```

#### Como analisar com GDB

```bash
gdb ./bin/double_free_bug
```

Comandos sugeridos:

```gdb
break main
run
next
print numbers
next
next
print numbers
bt
```

#### O que observar

- momento em que o ponteiro deixa de ser válido
- se o código ainda acessa `numbers[0]` depois de `free`
- stack trace do acesso inválido

---

### 3. `memory/realloc_misuse_bug.c`

#### Tipo de problema

Uso incorreto de `realloc`, com perda de referência para a memória original em caso de falha.

#### O que o programa faz

Tenta aumentar dinamicamente um buffer de inteiros.

#### O que investigar

- O retorno de `realloc` está sendo tratado de forma segura?
- O ponteiro antigo pode ser perdido?
- O código consegue lidar com falha de alocação sem vazar memória?

#### Como executar

```bash
./bin/realloc_misuse_bug
```

#### Como analisar

Primeiro leia o código. Depois tente identificar o problema lógico sem depender do comportamento do sistema operacional. Em seguida rode:

```bash
valgrind --leak-check=full --track-origins=yes ./bin/realloc_misuse_bug
```

#### O que observar

- uso direto do retorno de `realloc`
- ausência ou não de ponteiro temporário
- caminhos de falha e limpeza de memória

---

## CONCURRENCY

### 4. `concurrency/race_condition_bug.c`

#### Tipo de problema

Race condition em variável compartilhada.

#### O que o programa faz

Cria várias threads que incrementam um contador global.

#### O que investigar

- a operação `counter++` é atômica?
- múltiplas threads modificam o mesmo valor sem proteção?
- o valor final muda entre execuções?

#### Como executar

```bash
./bin/race_condition_bug
```

Rode várias vezes:

```bash
for i in $(seq 1 10); do ./bin/race_condition_bug; done
```

#### Como analisar com GDB

```bash
gdb ./bin/race_condition_bug
```

Comandos úteis:

```gdb
break increment_counter
run
info threads
print counter
continue
```

#### O que observar

- valor final abaixo do esperado
- interleaving entre threads
- natureza não atômica do incremento

#### Observação importante

`valgrind` tradicional ajuda pouco em race condition. Para esse caso, seu foco principal deve ser raciocínio sobre região crítica, exclusão mútua e repetição de execução.

---

### 5. `concurrency/deadlock_bug.c`

#### Tipo de problema

Possível deadlock por ordem inconsistente de aquisição de mutexes.

#### O que o programa faz

Duas threads tentam adquirir dois locks, mas em ordem diferente.

#### O que investigar

- cada thread pega os locks na mesma ordem?
- existe espera circular?
- o programa pode travar e nunca terminar?

#### Como executar

```bash
./bin/deadlock_bug
```

Você pode precisar rodar mais de uma vez até reproduzir o travamento.

#### Como analisar com GDB

Abra em um terminal:

```bash
gdb ./bin/deadlock_bug
```

Rode o programa e, se ele travar:

```gdb
run
# espere travar
info threads
thread 1
bt
thread 2
bt
```

#### O que observar

- uma thread esperando pelo lock segurado pela outra
- pilha de chamadas parada em `pthread_mutex_lock`
- ausência de progresso

#### Perguntas importantes

- há uma ordem global de aquisição de locks?
- é possível reduzir a área crítica?
- há outra abordagem menos propensa a deadlock?

---

### 6. `concurrency/shared_buffer_bug.c`

#### Tipo de problema

Produtor/consumidor simplificado com compartilhamento inseguro de buffer e sinalização incompleta.

#### O que o programa faz

Uma thread escreve em buffer compartilhado enquanto outra lê.

#### O que investigar

- existe sincronização suficiente?
- a thread consumidora pode ler conteúdo incompleto ou antigo?
- a sinalização de disponibilidade é confiável?

#### Como executar

```bash
./bin/shared_buffer_bug
```

#### Como analisar

Rode várias vezes. Adicione prints temporários se necessário. Se quiser usar `gdb`, coloque breakpoints nas funções `producer` e `consumer`.

```gdb
break producer
break consumer
run
info threads
```

#### O que observar

- leituras inconsistentes
- dependência em timing
- uso de variável compartilhada sem protocolo robusto

---

## DATA STRUCTURES

### 7. `data_structures/linked_list_leak_bug.c`

#### Tipo de problema

Vazamento em estrutura encadeada.

#### O que o programa faz

Cria uma lista ligada e imprime seus elementos.

#### O que investigar

- a estrutura é liberada ao final?
- a liberação deve ocorrer nó a nó?
- existe função específica de destruição?

#### Como executar

```bash
./bin/linked_list_leak_bug
```

#### Como analisar com Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/linked_list_leak_bug
```

#### O que observar

- vazamento dos nós
- efeito acumulado em estruturas dinâmicas maiores
- necessidade de política clara de ownership

---

### 8. `data_structures/linked_list_use_after_free_bug.c`

#### Tipo de problema

Uso de nó após liberação, causado por fluxo incorreto de remoção.

#### O que o programa faz

Remove um elemento de lista ligada e continua acessando ponteiro inválido.

#### O que investigar

- o encadeamento da lista é atualizado corretamente?
- existe referência pendurada para nó removido?
- o código imprime ou acessa campos depois de `free`?

#### Como executar

```bash
./bin/linked_list_use_after_free_bug
```

#### Como analisar com GDB

```bash
gdb ./bin/linked_list_use_after_free_bug
```

Sugestão:

```gdb
break remove_head
run
next
print head
print *head
next
bt
```

#### Como analisar com Valgrind

```bash
valgrind --track-origins=yes ./bin/linked_list_use_after_free_bug
```

#### O que observar

- leitura inválida após liberação
- ordem incorreta das operações de remoção
- necessidade de preservar o próximo nó antes de liberar o atual

---

## Estratégia recomendada de estudo

### Nível 1 — análise estática

Antes de rodar, tente marcar no próprio código:

- variáveis na stack
- alocações na heap
- regiões críticas
- ownership de ponteiros
- pontos de risco

### Nível 2 — execução normal

Rode o programa e anote:

- saída esperada
- saída obtida
- se falha sempre ou só às vezes

### Nível 3 — instrumentação

Use `printf` temporariamente para:

- endereços
- valores compartilhados
- ordem de execução
- identificador de thread

Exemplo:

```c
printf("thread=%lu counter=%d\n", (unsigned long)pthread_self(), counter);
```

### Nível 4 — depuração com ferramentas

- `valgrind` para memória
- `gdb` para fluxo, ponteiros, crash e threads

### Nível 5 — correção mínima

Primeiro corrija apenas o bug principal. Não tente refatorar tudo ao mesmo tempo.

### Nível 6 — correção robusta

Depois da primeira correção, pense em:

- tratamento de erro
- ownership claro
- cleanup centralizado
- legibilidade
- possibilidade de testes

---

## Sugestão de rotina de estudo

### Semana de memória

- Dia 1: `memory_leak_bug.c`
- Dia 2: `double_free_bug.c`
- Dia 3: `realloc_misuse_bug.c`
- Dia 4: repetir análises com `valgrind`
- Dia 5: corrigir e documentar o que aprendeu

### Semana de concorrência

- Dia 1: `race_condition_bug.c`
- Dia 2: `deadlock_bug.c`
- Dia 3: `shared_buffer_bug.c`
- Dia 4: analisar com `gdb`
- Dia 5: corrigir e comparar abordagens

### Semana de estruturas dinâmicas

- Dia 1: `linked_list_leak_bug.c`
- Dia 2: `linked_list_use_after_free_bug.c`
- Dia 3: rodar `valgrind`
- Dia 4: desenhar a lista em papel e rastrear ponteiros
- Dia 5: implementar função de destruição e remoção segura

---

## Ideias para expandir o repositório depois

Quando terminar estes desafios, você pode criar novas categorias:

- `processes/`
  - bugs com `fork`, `wait`, `exec`, pipes
- `files/`
  - bugs de leitura parcial, escrita incompleta, descritores não fechados
- `signals/`
  - bugs envolvendo `signal`, `sigaction`, interrupção de syscalls
- `network/`
  - bugs de socket, concorrência em servidor simples

---

## Observação final

Não trate este material como lista de exercícios para “passar”. Trate como laboratório de depuração. O objetivo não é apenas encontrar o bug; é aprender a pensar como alguém que investiga sistemas reais.
