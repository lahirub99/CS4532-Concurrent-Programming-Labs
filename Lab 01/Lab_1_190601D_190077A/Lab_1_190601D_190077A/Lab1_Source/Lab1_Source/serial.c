#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "serial.h"
#include "global.h"
#include "helper_func.h"

unsigned long test_serial_run(int case_num){

    node *head = NULL;
    float mmem;
    float mins;
    float mdel;

    int m = 10000; //Number of operations
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

    // Fractions of each operation
    int num_Mem = (int) (m * mmem);
    int num_Ins = (int)(m * mins);
    int num_Del= (int)( m * mdel);

    int n = 1000; //Number of elements in the list
    int count = 0;

    int op_arr[m];

    // Generate a linked list with n random numbers
    srand(time(0));
    
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

    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL); 
    for (int j=0;j<m;j++){
        int operation = op_arr[j];
        int randVal = rand()%65535;
        switch (operation) {
            case 0:
                Member(randVal,head);
                break;
            case 1:
                Insert(randVal,&head);
                break;
            case 2:
                Delete(randVal,&head);
                break;
            default:
                printf("Unknown value.\n");
        }
    }

    gettimeofday(&stop, NULL);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    destructor(head);
    printf("Serial ran!\n");
    return time;
}

