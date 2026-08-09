#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

void *tF(void *par)
{
    int *tidP;
    int tid;

    tidP = (int *)par;
    tid = *tidP;

    printf("Thread read t = %d\n", tid);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t th[NUM_THREADS];
    int rc;
    int t;

    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&th[t], NULL, tF, (void *)&t);

        if (rc != 0)
        {
            exit(-1);
        }
    }

    pthread_exit(NULL);
}