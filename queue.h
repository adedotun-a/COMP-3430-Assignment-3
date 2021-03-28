
// queue.h
#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include <stdio.h>
#include <string.h>
#include "task.h"
// #define ERROR -1000

typedef struct QNode node;

//Queue
node *addToQueue(node *head, task *task);
node *sortQueue(node *head);
#endif
