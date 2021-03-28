
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
    char *task_name;
    taskType taskType;
    int priority;
    int task_length;
    int odds_of_IO;
} task;

typedef struct METRICS
{
    int priority;
    int time;
    taskType type;
} metrics;

typedef enum POLICY
{
    PRR,
    STCF,
    MLQ,
} policy;

#endif