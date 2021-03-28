
// queue.h
#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include <stdio.h>
#include <string.h>
#include <task.h>
// #define ERROR -1000

typedef struct QUEUE Queue;

//Queue
void initQueue(Queue *rdy, int size);
Queue *makeQueue(void);
int compare(task *a, task *b, char *key);
void queuePty(Queue *rdy, task *newProc, char *key);
void queue(Queue *rdy, task *newProc);
int size(Queue *rdy);
task *peek(Queue *rdy);
int getLimit(Queue *rdy);
task *dequeue(Queue *rdy);
void clearQueue(Queue *ready);

#endif
