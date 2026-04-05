#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 100000

int counter = 0;

void *increment_counter(void *arg) {
    (void)arg;
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        counter++;
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Counter final: %d\n", counter);
    return 0;
}
