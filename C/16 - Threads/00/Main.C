#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Function executed by the created thread.
 *
 * pthread thread functions must have this general form:
 *
 *     void *function_name(void *arg)
 *
 * In this example, we do not need to pass any argument,
 * so "arg" will receive NULL.
 */
void *tF(void *arg)
{
    // Print a message from the created thread.
    printf("Created thread is running\n");

    /*
     * Terminate ONLY this created thread.
     *
     * NULL means that this thread does not return
     * any termination value/status to another thread.
     */
    pthread_exit(NULL);
}


int main(void)
{
    /*
     * Variable used to store the identifier
     * of the thread that we are going to create.
     */
    pthread_t tid;

    /*
     * Variable used to store the return value
     * of pthread_create().
     *
     * pthread_create() returns:
     *   0       -> success
     *   nonzero -> error
     */
    int rc;


    /*
     * Create one new thread.
     *
     * Arguments:
     *
     * &tid
     *     Address where pthread_create() stores
     *     the identifier of the new thread.
     *
     * NULL
     *     Use the default thread attributes.
     *
     * tF
     *     The function that the new thread starts executing.
     *
     * NULL
     *     No argument is passed to tF().
     */
    rc = pthread_create(
        &tid,       // Store the new thread ID here
        NULL,       // Default attributes
        tF,         // Function executed by the new thread
        NULL        // No argument passed to the thread
    );


    /*
     * Check whether the thread was created successfully.
     */
    if (rc != 0)
    {
        // Thread creation failed.
        printf("Error creating thread\n");

        /*
         * exit() terminates the WHOLE process.
         * Therefore, all threads of this process terminate.
         */
        exit(-1);
    }


    /*
     * This instruction is executed by the main thread.
     *
     * After pthread_create(), the main thread and the
     * created thread may execute concurrently.
     */
    printf("Main thread is running\n");


    /*
     * Terminate ONLY the main thread.
     *
     * This is important:
     *
     * pthread_exit(NULL)
     *     -> terminates only the main thread
     *     -> other created threads can continue running
     *
     * return 0;
     * or
     * exit(0);
     *
     *     -> would terminate the whole process
     *     -> all threads would terminate
     */
    pthread_exit(NULL);
}