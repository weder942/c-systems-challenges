#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char buffer[64];
int ready = 0;

void *producer(void *arg) {
    (void)arg;
    strcpy(buffer, "mensagem produzida pela thread produtora");
    ready = 1;
    return NULL;
}

void *consumer(void *arg) {
    (void)arg;
    while (!ready) {
        /* busy wait */
    }

    printf("Consumidor leu: %s\n", buffer);
    return NULL;
}

int main(void) {
    pthread_t prod, cons;

    pthread_create(&cons, NULL, consumer, NULL);
    usleep(1000);
    pthread_create(&prod, NULL, producer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
