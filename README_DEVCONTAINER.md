# Devcontainer mínimo para estudos de C

Esse ambiente foi pensado para ser o mais enxuto possível, usando `ubuntu:24.04` e só com o necessário para:

- compilar C
- usar `make`
- debugar com `gdb`
- analisar memória com `valgrind`

## O que vem instalado

- `build-essential`
- `gdb`
- `valgrind`
- `clang`
- `clang-format`
- `make`
- `git`

## Estrutura

- `.devcontainer/devcontainer.json`
- `Dockerfile`

## Como usar no VS Code

1. Abra a pasta do projeto no VS Code.
2. Instale a extensão **Dev Containers** da Microsoft.
3. Garanta que o Docker Desktop esteja rodando.
4. Abra a paleta de comandos.
5. Rode:

```text
Dev Containers: Reopen in Container
```

## Observações para Mac M2

Esse setup evita peso desnecessário e deve funcionar bem no Apple Silicon.
A imagem `ubuntu:24.04` é multi-arch, então o Docker tende a puxar a variante correta para ARM64.

## Comandos úteis

Compilar:

```bash
gcc -Wall -Wextra -g arquivo.c -o programa
```

Rodar com valgrind:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./programa
```

Abrir no gdb:

```bash
gdb ./programa
```

## Dica

Para seus estudos de C, prefira compilar com símbolos de debug:

```bash
gcc -Wall -Wextra -g arquivo.c -o programa
```

Isso melhora bastante a experiência no `gdb` e em mensagens do `valgrind`.
