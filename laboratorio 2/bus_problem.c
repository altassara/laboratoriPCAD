#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "my_semaphore.h"

#define BUS_CAPACITY 5
#define NUM_PASSENGERS 10

my_semaphore boarding_permission;
my_semaphore disembark_permission;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int boarded = 0;
int disembarked = 0;

void *bus_thread(void *arg)
{
    while (1)
    {
        for (int i = 0; i < BUS_CAPACITY; i++)
        {
            my_sem_signal(&boarding_permission);
        }

        while (1)
        {
            pthread_mutex_lock(&mutex);
            if (boarded == BUS_CAPACITY)
            {
                boarded = 0;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            usleep(10000);
        }

        printf("Il bus è pieno. Parto per il tour.\n");
        sleep(3);
        printf("Tour finito. Concedo il permesso di scendere.\n");

        for (int i = 0; i < BUS_CAPACITY; i++)
        {
            my_sem_signal(&disembark_permission);
        }

        while (1)
        {
            pthread_mutex_lock(&mutex);
            if (disembarked == BUS_CAPACITY)
            {
                disembarked = 0;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            usleep(10000);
        }

        printf("Tutti i passeggeri sono scesi. Pronto per una nuova corsa.\n\n");
    }
    return NULL;
}

void *passenger_thread(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    while (1)
    {
        my_sem_wait(&boarding_permission);
        printf("Passeggero %d è salito sul bus.\n", id);

        pthread_mutex_lock(&mutex);
        boarded++;
        pthread_mutex_unlock(&mutex);

        my_sem_wait(&disembark_permission);
        printf("Passeggero %d è sceso dal bus.\n", id);

        pthread_mutex_lock(&mutex);
        disembarked++;
        pthread_mutex_unlock(&mutex);

        sleep(1 + rand() % 3);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t bus;
    pthread_t passengers[NUM_PASSENGERS];

    my_sem_init(&boarding_permission, 0);
    my_sem_init(&disembark_permission, 0);

    pthread_create(&bus, NULL, bus_thread, NULL);

    for (int i = 0; i < NUM_PASSENGERS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&passengers[i], NULL, passenger_thread, id);
    }

    pthread_join(bus, NULL);
    for (int i = 0; i < NUM_PASSENGERS; i++)
    {
        pthread_join(passengers[i], NULL);
    }

    my_sem_destroy(&boarding_permission);
    my_sem_destroy(&disembark_permission);
    pthread_mutex_destroy(&mutex);

    return 0;
}