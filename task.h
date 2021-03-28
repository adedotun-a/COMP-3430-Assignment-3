
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

#endif