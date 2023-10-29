// Pthreads
// Fork-Join Pattern
// This program creates a group of threads to perform a fork-join pattern
//
// History:
// Who          When           What
// ---------   -----------    ----------------------------------------------
// jfloresx     01/01/2020     Created forkJoin.c
//
// Compile:  gcc -g -Wall -o forkJoin forkJoin.c -lpthread
// Run:      ./forkJoin <number of threads>
//
// Input:    none
// Output:   A message from each thread
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// // Global variable:  accessible to all threads
// int thread_count;

// void *Hello(void* rank);  // Thread function

// int main(int argc, char* argv[]) {
//     long       thread;  // Use long in case of a 64-bit system
//     pthread_t* thread_handles;

//     // Get number of threads from command line
//     thread_count = strtol(argv[1], NULL, 10);

//     thread_handles = malloc (thread_count*sizeof(pthread_t));

//     for (thread = 0; thread < thread_count; thread++)
//         pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);

//     printf("Hello from the main thread\n");

//     for (thread = 0; thread < thread_count; thread++)
//         pthread_join(thread_handles[thread], NULL);

//     free(thread_handles);

//     return 0;
// }  /* main */

for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);


// OpenMP example
#include <omp.h>

# pragma omp parallel num_threads(thread_count) Hello();











