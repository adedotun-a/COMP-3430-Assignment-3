
// queue.h
#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include <stdio.h>
#include <string.h>
#include "task.h"
// #define ERROR -1000

typedef struct QNode
{
    TASK *task;
    struct QNode *next;
} node;

//Queue
node *enQueue(node *head, TASK *task);
node *sortQueue(node *head);
#endif
