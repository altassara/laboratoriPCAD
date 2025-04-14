#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "my_semaphore.h"
#define N 5

my_semaphore ticket;
my_semaphore sticks[N];

void *philosopher(void *arg)
{
    int id = (intptr_t)arg;

    for (int i = 0; i < N; i++)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        printf("Philosopher %d is hungry\n", id);

        my_sem_wait(&ticket);

        int rightStickIdx = (id - 1 + N) % N;
        int leftStickIdx = id;

        printf("Philosopher %d is trying to get left stick number %d\n", id, leftStickIdx);

        my_sem_wait(&sticks[leftStickIdx]);

        printf("Philosopher %d has left stick number %d\n", id, leftStickIdx);
        sleep(1);

        printf("Philosopher %d is trying to get right stick number %d\n", id, rightStickIdx);

        my_sem_wait(&sticks[rightStickIdx]);

        printf("Philosopher %d has right stick number %d\n", id, rightStickIdx);
        sleep(1);

        printf("Philosopher %d is eating\n", id);
        sleep(1);
        printf("Philosopher %d has finished eating\n", id);

        my_sem_signal(&sticks[leftStickIdx]);
        my_sem_signal(&sticks[rightStickIdx]);

        my_sem_signal(&ticket);
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[N];

    if (my_sem_init(&ticket, N - 1) != 0)
    {
        fprintf(stderr, "Errore nella creazione del semaforo ticket");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
    {
        if (my_sem_init(&sticks[i], 1))
        {
            fprintf(stderr, "Errore nella creazione del semaforo %d\n", i);
            exit(EXIT_FAILURE);
        }

        if (pthread_create(&philosophers[i], NULL, philosopher, (void *)(intptr_t)i))
        {
            fprintf(stderr, "Errore nella creazione del thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (pthread_join(philosophers[i], NULL))
        {
            fprintf(stderr, "Errore nella terminazione del thread %d\n", i);
            exit(EXIT_FAILURE);
        }

        if (my_sem_destroy(&sticks[i]))
        {
            fprintf(stderr, "Errore nella eliminazione del semaforo %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (my_sem_destroy(&ticket))
    {
        fprintf(stderr, "Errore nella eliminazione del semaforo ticket");
        exit(EXIT_FAILURE);
    }

    return 0;
}
