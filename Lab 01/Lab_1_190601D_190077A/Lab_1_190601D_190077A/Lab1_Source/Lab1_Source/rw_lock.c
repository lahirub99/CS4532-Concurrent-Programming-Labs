#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "rw_lock.h"
#include "global.h"
#include "helper_func.h"

void *threadFunc_rw(void* rank);


unsigned long test_rw_lock_run(int case_num, int thread_count){
//    rw_lock_data thread_data;
    node* head = NULL;
    int n = 1000;
    //thread_data.thread_count = thread_count; // Number of threads 
    int m = 10000; //Number of operations
    float mmem;
    float mins;
    float mdel;

    switch (case_num)
    {
        case 1:{
            mmem = 0.99;
            mins = 0.005;
            mdel = 0.005;
            break;
        }

        case 2:{
            mmem = 0.9;
            mins = 0.05;
            mdel = 0.05;
            break;
        }

        case 3:{
            mmem = 0.5;
            mins = 0.25;
            mdel = 0.25;
            break;
        }
        
        default:{
            mmem = 0.99;
            mins = 0.005;
            mdel = 0.005;
            break;
        }
    }

    int num_Mem = (int) (m * mmem);
    int num_Ins = (int)(m * mins);
    int num_Del= (int)( m * mdel);
    int op_arr[m];

    int nodes = 0;
    while (nodes < n){
        int randVal = rand()%65535;
        if (Member(randVal,head)==1){
            continue;
        }
        Insert(randVal, &head);
        nodes++;
    }
    int i;
    for (i = 0; i < num_Mem; i++) {
        op_arr[i] = 0;
    }
    for (; i < num_Mem + num_Ins; i++) {
        op_arr[i] = 1;
    }

    for (; i < num_Mem + num_Ins + num_Del; i++) {
        op_arr[i] = 2;
    }
    shuffle(op_arr,m);

    // Initializing the mutex
    pthread_rwlock_t* rw_lock = malloc(sizeof (pthread_rwlock_t));
    pthread_rwlock_init(rw_lock, NULL);

    pthread_t thread_handles[thread_count];
    rw_lock_data thread_args[thread_count];
    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL);

    for (int thread=0; thread < thread_count ; thread++){
        thread_args[thread] = (rw_lock_data){
                rw_lock,
                head,
                thread_count,
                op_arr,
                m,
                thread,
        };
        pthread_create(&thread_handles[thread],NULL,threadFunc_rw,(void*) &thread_args[thread]);
    }


    for (int thread=0; thread<thread_count ; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    //Function call
    gettimeofday(&stop, NULL);
    pthread_rwlock_destroy(rw_lock);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    destructor(head);
    printf("RW_lock ran!\n");
    return time;
}

void *threadFunc_rw(void * t_data){
    rw_lock_data * thread_data = (rw_lock_data *)t_data;
    int my_rank = (int) thread_data->rank;
    int local_m = thread_data->m/thread_data->thread_count;
    // int local_m=2;
    int my_start = my_rank*local_m;
    int my_last = (my_rank+1)*local_m-1;
    for (int i=my_start;i<my_last;i++){
        int operation = thread_data->op_arr[i];
        int randVal = rand()%65535;
        switch (operation) {
            case 0:
                pthread_rwlock_rdlock(thread_data->rwlock);
                Member(randVal,thread_data->head);
                pthread_rwlock_unlock(thread_data->rwlock);
                break;
            case 1:
                pthread_rwlock_wrlock(thread_data->rwlock);
                Insert(randVal,&thread_data->head);
                pthread_rwlock_unlock(thread_data->rwlock);
                break;
            case 2:
                pthread_rwlock_wrlock(thread_data->rwlock);
                Delete(randVal,&thread_data->head);
                pthread_rwlock_unlock(thread_data->rwlock);
                break;
            default:
                printf("Unknown value.\n");
        }

    }
}