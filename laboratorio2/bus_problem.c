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

my_semaphore full_bus;
my_semaphore empty_bus;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int boarded = 0;

void *bus_thread(void *arg)
{
    while (1)
    {
        // segnalo a BUS_CAPACITY passeggeri che possono salire
        for (int i = 0; i < BUS_CAPACITY; i++)
        {
            my_sem_signal(&boarding_permission);
        }

        // prima di partire aspetto che il bus sia pieno
        my_sem_wait(&full_bus);

        printf("Bus pieno, partiamo!!!.\n");
        sleep(2);
        printf("Tour finito, i passaggeri possono scendere\n");

        // segnalo a BUS_CAPACITY passeggeri che possono scendere
        for (int i = 0; i < BUS_CAPACITY; i++)
        {
            my_sem_signal(&disembark_permission);
        }

        my_sem_wait(&empty_bus);

        printf("Bus vuoto, pronto per nuova corsa, aridaje!\n\n");
    }
    return NULL;
}

void *passenger_thread(void *arg)
{
    int id = (intptr_t)arg;
    while (1)
    {
        my_sem_wait(&boarding_permission);

        // l'ultimo segnala che sale segnala che il bus è pieno
        pthread_mutex_lock(&mutex);
        boarded++;
        printf("Passeggero %d è salito sul bus.\n", id);
        if (boarded == BUS_CAPACITY)
        {
            my_sem_signal(&full_bus);
        }
        pthread_mutex_unlock(&mutex);

        my_sem_wait(&disembark_permission);

        // l'ultimo che scende segnala che il bus è vuoto
        pthread_mutex_lock(&mutex);
        boarded--;
        printf("Passeggero %d è sceso dal bus.\n", id);
        if (boarded == 0)
        {
            my_sem_signal(&empty_bus);
        }
        pthread_mutex_unlock(&mutex);

        // i passaggeri attendono un tempo casuale prima di riporvare a salire
        useconds_t delay = rand() % 3000001;
        usleep(delay);
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
    my_sem_init(&full_bus, 0);
    my_sem_init(&empty_bus, 0);

    if (pthread_create(&bus, NULL, bus_thread, NULL))
    {
        fprintf(stderr, "Errore nella creazione del thread bus\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_PASSENGERS; i++)
    {
        if (pthread_create(&passengers[i], NULL, passenger_thread, (void *)(intptr_t)i))
        {
            fprintf(stderr, "Errore nella creazione del thread passeggero %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    pthread_join(bus, NULL);
    for (int i = 0; i < NUM_PASSENGERS; i++)
    {
        if (pthread_join(passengers[i], NULL))
        {
            fprintf(stderr, "Errore nella join del thread passeggero %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    my_sem_destroy(&boarding_permission);
    my_sem_destroy(&disembark_permission);
    my_sem_destroy(&full_bus);
    my_sem_destroy(&empty_bus);
    pthread_mutex_destroy(&mutex);

    return 0;
}