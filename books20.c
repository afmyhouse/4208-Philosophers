#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t book=PTHREAD_MUTEX_INITIALIZER;

void *Allen(void *arg);
void *Bob(void *arg);

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, *Allen, NULL);
    pthread_create(&tid2, NULL, *Bob, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

void *Allen(void *arg) {
    pthread_mutex_lock(&book);
    printf("I'm Allen, I borrow this book and I won't return it!\n");
    pthread_mutex_unlock(&book);
    printf("I'm Allen, I just returned it!\n");
}

void *Bob(void *arg) {
    pthread_mutex_lock(&book);
    printf("I'm Bob, I can borrow it now\n");
}