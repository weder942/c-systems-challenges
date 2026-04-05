#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;

void *thread_one(void *arg) {
    (void)arg;
    pthread_mutex_lock(&lock_a);
    usleep(100000);
    pthread_mutex_lock(&lock_b);

    printf("Thread 1 acquired both locks\n");

    pthread_mutex_unlock(&lock_b);
    pthread_mutex_unlock(&lock_a);
    return NULL;
}

void *thread_two(void *arg) {
    (void)arg;
    pthread_mutex_lock(&lock_b);
    usleep(100000);
    pthread_mutex_lock(&lock_a);

    printf("Thread 2 acquired both locks\n");

    pthread_mutex_unlock(&lock_a);
    pthread_mutex_unlock(&lock_b);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_one, NULL);
    pthread_create(&t2, NULL, thread_two, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
