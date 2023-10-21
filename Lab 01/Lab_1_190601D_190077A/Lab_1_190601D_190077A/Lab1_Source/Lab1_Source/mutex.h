#ifndef MUTEX_RUN_H
#define MUTEX_RUN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

struct mutex_data
{
    pthread_mutex_t *mutex;
    node *head;
    int m; //Number of operations
    int* op_arr;

    int thread_count; // Number of threads 
    int rank;
};
typedef struct mutex_data mutex_data;

unsigned long test_mutex_run(int case_num, int thread_count);

#endif