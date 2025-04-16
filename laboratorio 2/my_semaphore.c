#include "my_semaphore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

int my_sem_init(my_semaphore *S, unsigned int v)
{
    S->V = v;
    if (pthread_mutex_init(&(S->lock), NULL))
    {
        fprintf(stderr, "pthread_mutex_init failed\n");
        return -1;
    }
    if (pthread_cond_init(&(S->varcond), NULL))
    {
        fprintf(stderr, "pthread_cond_init failed\n");
        return -1;
    }
    return 0;
}

int my_sem_wait(my_semaphore *S)
{
    pthread_mutex_lock(&(S->lock));
    while (S->V == 0)
    {
        pthread_cond_wait(&(S->varcond), &(S->lock));
    }
    S->V--;
    pthread_mutex_unlock(&(S->lock));
    return 0;
}

int my_sem_signal(my_semaphore *S)
{
    pthread_mutex_lock(&(S->lock));
    S->V++;
    pthread_cond_signal(&(S->varcond));
    pthread_mutex_unlock(&(S->lock));
    return 0;
}

int my_sem_destroy(my_semaphore *S)
{
    if (pthread_mutex_destroy(&(S->lock)))
    {
        fprintf(stderr, "pthread_mutex_destroy failed\n");
        return -1;
    }
    if (pthread_cond_destroy(&(S->varcond)))
    {
        fprintf(stderr, "pthread_cond_destroy failed\n");
        return -1;
    }

    return 0;
}
