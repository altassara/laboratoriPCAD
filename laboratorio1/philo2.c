#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5

pthread_mutex_t sticks[N];

void *philosopher(void *arg)
{
    int id = (intptr_t)arg;

    for (int i = 0; i < N; i++)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        printf("Philosopher %d is hungry\n", id);

        int rightStickIdx = (id - 1 + N) % N;
        int leftStickIdx = id;

        if (id == 0)
        {
            printf("Philosopher %d is trying to get right stick number %d\n", id, rightStickIdx);
            pthread_mutex_lock(&sticks[rightStickIdx]);
            printf("Philosopher %d has right stick number %d\n", id, rightStickIdx);
            sleep(1);

            printf("Philosopher %d is trying to get left stick number %d\n", id, leftStickIdx);
            pthread_mutex_lock(&sticks[leftStickIdx]);
            printf("Philosopher %d has left stick number %d\n", id, leftStickIdx);
        }
        else
        {
            printf("Philosopher %d is trying to get left stick number %d\n", id, leftStickIdx);
            pthread_mutex_lock(&sticks[leftStickIdx]);
            printf("Philosopher %d has left stick number %d\n", id, leftStickIdx);
            sleep(1);

            printf("Philosopher %d is trying to get right stick number %d\n", id, rightStickIdx);
            pthread_mutex_lock(&sticks[rightStickIdx]);
            printf("Philosopher %d has right stick number %d\n", id, rightStickIdx);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(1);
        printf("Philosopher %d has finished eating\n", id);

        pthread_mutex_unlock(&sticks[leftStickIdx]);
        pthread_mutex_unlock(&sticks[rightStickIdx]);
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[N];

    for (int i = 0; i < N; i++)
    {
        if (pthread_mutex_init(&sticks[i], NULL))
        {
            fprintf(stderr, "Errore nella creazione del mutex %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++)
    {
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
    }

    for (int i = 0; i < N; i++)
    {
        if (pthread_mutex_destroy(&sticks[i]))
        {
            fprintf(stderr, "Errore nella eliminazione del mutex %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}