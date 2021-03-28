
// task.h
#ifndef TASK_HEADER
#define TASK_HEADER

//Task Type ID
typedef enum ID
{
    shortTask,
    medTask,
    longTask,
    ioTask
} taskType;

//task struct
typedef struct TASK
{
    char *taskName;
    taskType taskType;
    int priority;
    int taskLength;
    int oddsOfIO;
} task;

typedef enum POLICY
{
    PRR,
    STCF,
    MLQ,
} policy;

#endif
