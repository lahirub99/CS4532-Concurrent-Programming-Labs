#ifndef RW_LOCK_H
#define RW_LOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

struct rw_lock_data
{
    pthread_rwlock_t *rwlock;
    node *head;

    int thread_count; // Number of threads 
    int* op_arr;
    int m; //Number of operations
    int rank;
};
typedef struct rw_lock_data rw_lock_data;

unsigned long test_rw_lock_run(int case_num, int thread_count);

#endif