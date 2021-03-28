
// queue.h
#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include <stdio.h>
#include <string.h>
// #define ERROR -1000

typedef struct QUEUE Queue;

//Task Type ID
typedef enum ID
{
    shortTask,
    medTask,
    longTask,
    ioTask
} id;

//task struct
typedef struct TASK
{
    char *task_name;
    id task_type;
    int priority;
    int task_length;
    int odds_of_IO;
} task;

typedef struct METRICS
{
    int priority;
    int time;
    id type;
} metrics;

typedef enum POLICY
{
    PRR,
    STCF,
    MLQ,
} policy;

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
