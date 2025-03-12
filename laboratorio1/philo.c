#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#define N 5

bool sticks[N] = {false, false, false, false, false};

void *philosopher(void *arg)
{
    int id = (intptr_t)arg;
    printf("id: %d\n", id);
    bool ownSticks[2] = {false, false};

    while (true)
    {

        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        printf("Philosopher %d is hungry\n", id);
        int rightStickIdx = (id - 1 + N) % N;
        int leftStickIdx = id;
        printf("Philosopher %d is trying to get left stick number %d\n", id, leftStickIdx);
        printf("Philosopher %d is trying to get right stick number %d\n", id, rightStickIdx);
        if (!sticks[leftStickIdx])
        {
            sticks[leftStickIdx] = true;
            ownSticks[0] = true;
            printf("Philosopher %d caught stick number %d\n", id, leftStickIdx);
            sleep(1);
        }

        if (!sticks[rightStickIdx])
        {
            sticks[rightStickIdx] = true;
            ownSticks[1] = true;
            printf("Philosopher %d caught stick number %d\n", id, rightStickIdx);
            sleep(1);
        }

        if (ownSticks[0] && ownSticks[1])
        {
            printf("Philosopher %d is eating\n", id);
            sleep(1);
            printf("Philosopher %d has finished eating\n", id);
            sticks[leftStickIdx] = false;
            sticks[rightStickIdx] = false;
            ownSticks[0] = false;
            ownSticks[1] = false;
        }
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[N];

    for (int i = 0; i < N; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)(intptr_t)i);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
