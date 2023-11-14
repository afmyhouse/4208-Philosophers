

// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

sem_t mutex;

void* mythread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");

    //critical section
	for(int i = 0; i < 2; i++)
	{
		printf("my thread i = %d\n", i);
		sleep(1);
	}

    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}
void* yourthread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");

    //critical section
    for(int i = 0; i < 2; i++)
	{
		printf("your thread i = %d\n", i);
		sleep(1);
	}

    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}

int main()
{
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
	system("clear");
    pthread_create(&t1,NULL,mythread,NULL);
    // sleep(2);
    pthread_create(&t2,NULL,yourthread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);

	sem_unlink("testesemaphore");
	sem_t *sem = sem_open("testesemaphore", O_CREAT, 0644, 1);
	printf("sem = %p\n", sem);
	sem_close(sem);
    return 0;
}
