#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable : accesible to all threads */
int thread_count;

void *Hello(void *rank); /* Thread function */

int main(int argc, char *argv[]) {
    long thread;    /* Use long in case of a 64-bit system */
    pthread_t * thread_handles;

    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);   // strtol - Convert string to long

    thread_handles = malloc(thread_count * sizeof(pthread_t));      // Allocate memory for thread handles. Malloc returns a void pointer. So, we need to typecast it to pthread_t

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Hello, (void *) thread);   
        /* Create threads. 
        pthread_create returns 0 if successful. 
        Arguments: thread handle, thread attribute, thread function, thread function argument */
    }

    printf("Hello from the main thread\n");

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);    
        /* Wait for all threads to complete. 
        pthread_join function used to wait for a thread to complete.
        Arguments: thread handle, thread return value */
    }

    free(thread_handles);   // Free memory allocated for thread handles
    return 0;
}