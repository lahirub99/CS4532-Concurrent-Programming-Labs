#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"


void destructor(node* head_p){
    node* curr_p = head_p;
    node* temp_p = NULL;

    while (NULL != curr_p)
    {
        temp_p = curr_p;
        curr_p = curr_p->next;
//        free(temp_p);
    }
    //printf("Entire linked list destructed!!\n");
}

int Member(int value, node* head_p){
    node *curr_p = head_p;
    int ret_value;

    while (curr_p != NULL && curr_p -> data < value){
        curr_p = curr_p->next;
    }

    if (NULL == curr_p || curr_p -> data > value){
        ret_value = 0;
    }
    else{
        ret_value = 1;
    }
    
    return ret_value;
}

int Insert(int value, node** head_p){
    node *curr_p = *head_p;
    node *pred_p = NULL;
    node *temp_p = NULL;
    int ret_value;

    while (NULL != curr_p && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if(NULL == curr_p || curr_p->data > value){
        temp_p = (node *) malloc(sizeof(node));
        temp_p -> data = value;
        temp_p -> next = curr_p;

        if(NULL == pred_p){
            *head_p = temp_p;
        }
        else{
            pred_p -> next = temp_p;
        }
        ret_value = 1;
    }
    else{
        ret_value = 0;
    }
    return ret_value;
}

int Delete(int value, node ** head_p){
    node *curr_p = *head_p;
    node *pred_p = NULL;
    int ret_val;

    while (NULL != curr_p && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if (NULL != curr_p && curr_p->data == value){
        if (NULL == pred_p){
            *head_p = curr_p ->next;
//            free(curr_p);
        }
        else{
            pred_p->next = curr_p->next;
//            free(curr_p);
        }
        ret_val = 1;
    }
    else{
        ret_val = 0;
    }
    return ret_val;
}

void Print(node *head_p){
    node *curr_p = head_p;

    while (NULL != curr_p){
        printf("node: %d \n",curr_p->data);
        curr_p = curr_p->next;
    }
}