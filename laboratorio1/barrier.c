#include "my_barrier.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 5

unsigned int pthread_my_barrier_init(my_barrier *mb, unsigned int v)
{
    if (v == 0)
        return 1;

    mb->vinit = v;
    mb->val = 0;

    if (pthread_mutex_init(&mb->lock, NULL) != 0)
        return 1;

    if (pthread_cond_init(&mb->varcond, NULL) != 0)
        return 1;

    return 0;
}

unsigned int pthread_my_barrier_wait(my_barrier *mb)
{
    pthread_mutex_lock(&mb->lock);

    mb->val++;

    if (mb->val >= mb->vinit)
    {
        mb->val = 0;
        pthread_cond_broadcast(&mb->varcond);
        pthread_mutex_unlock(&mb->lock);
        return 1;
    }
    else
    {
        pthread_cond_wait(&mb->varcond, &mb->lock);
        pthread_mutex_unlock(&mb->lock);
        return 0;
    }
}

my_barrier barrier;

void *thread_function(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d: raggiunto il punto di sincronizzazione.\n", id);

    unsigned int res = pthread_my_barrier_wait(&barrier);

    if (res == 1)
        printf("Thread %d: sono l'ultimo, sveglio gli altri\n", id);
    else
        printf("Thread %d: sono stato svegliato\n", id);

    return NULL;
}

int main()
{
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];

    if (pthread_my_barrier_init(&barrier, THREAD_COUNT) != 0)
    {
        fprintf(stderr, "Errore: inizializzazione della barriera fallita.\n");
        return 1;
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &ids[i]);
        sleep(1);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Tutti i thread hanno superato la barriera!\n");
    return 0;
}