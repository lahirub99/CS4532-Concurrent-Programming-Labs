#ifndef CUS_LINKED_LIST_H
#define CUS_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node {
  int data;
  struct node * next;
  pthread_mutex_t mutex;
};

typedef struct node node;

void destructor(node* head_p);
int Member(int value, node *head_p);
int Insert(int value, node **head_p);
int Delete(int value, node **head_p);
void Print(node * head_p);

#endif