/*
* COURSE: COMP 3340 SECTION [A02]
* INSTRUCTOR: Rasit Eskicioglu
* NAME: Adedotun Adeyemo
* STUDENT ID: 7784807
* ASSIGNMENT: 3
* QUESTION: 1
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>
#include "queue.h"

#define MAXNUM 100

//Variables
int countType[4] = {0, 0, 0, 0};
int countPriority[3] = {0, 0, 0};

int totalTypeTime[4] = {0, 0, 0, 0};
int totalPriorityTime[3] = {0, 0, 0};

POLICY policy;
int timeSlice = 5;

int run = 1;

node *queues[3];
node *queue0; //priority 0 queue (high)
node *queue1; //priority 1  queue (med)
node *queue2; //priority 2 squeue (low)

//declaring condition variables
pthread_cond_t task_avail = PTHREAD_COND_INITIALIZER;
pthread_cond_t cpu_avail = PTHREAD_COND_INITIALIZER;
// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void initQueue();
void *CPU();
void printMetrics();
TASK *getTask();
void returnTask(TASK *t);
TASK *SJF();
TASK *roundRobin();
TASK *MLFQueue();
void *dispatcher();

// main
int main(int argc, char *argv[])
{
    if (argc < 3) //Check if commandline arguments are valid
    {
        printf("Please enter the no of CPUs and chosen scheduling policy\n");
        return -1;
    }

    int numCores = atoi(argv[1]);
    if (strcmp(argv[2], "rr") == 0)
    {
        policy = PRR;
    }
    else if (strcmp(argv[2], "stcf") == 0)
    {
        policy = STCF;
    }
    else if (strcmp(argv[2], "mlfq") == 0)
    {
        policy = MLQ;
    }
    else
    {
        printf("Please enter a valid policy\n");
        return -1;
    }
    printf("Using pure round-robin with %d CPUs.\n", numCores);
    initQueue();
    // numCores += 0;
    pthread_t *pIds = malloc(sizeof(pthread_t) * numCores);
    for (int i = 0; i < numCores; i++) //create threads for CPUS
    {
        pthread_create(&pIds[i], NULL, CPU, NULL);
    }

    pthread_t tid1;

    pthread_create(&tid1, NULL, dispatcher, NULL); //create thread for sheduler
    for (int i = 0; i < numCores; i++)
    {
        pthread_join(pIds[i], NULL);
    }
    printMetrics();
}

void update_metrics(int priority, int time, taskType type)
{
    //update metric arrays
    countType[type] += 1;
    countPriority[priority] += 1;
    totalTypeTime[type] += time;
    totalPriorityTime[priority] += time;
}

void *dispatcher()
{ //alert the CPUs that a task is available
    int runDispatch = 1;
    while (runDispatch == 1)
    {
        pthread_mutex_lock(&lock);

        pthread_cond_signal(&task_avail);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

void initQueue()
{
    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL)
    {
        printf("I/O Error, unable to open file!\n");
        exit(1);
    }

    TASK *temp = malloc(sizeof(TASK));
    while (fscanf(file, "%s %d %d %d %d\n", temp->taskName, &(temp->taskType), &(temp->priority), &(temp->taskLength), &(temp->oddsOfIO)) == 5)
    {
        // printf("%s %d %d %d %d\n", temp->taskName, temp->taskType, temp->priority, temp->taskLength, temp->oddsOfIO);
        if (policy == MLQ)
        {
            if (temp->priority == 0)
            {
                queue0 = addToQueue(queue0, temp);
            }
            else if (temp->priority == 1)
            {
                queue1 = addToQueue(queue1, temp);
            }
            else
            {
                queue2 = addToQueue(queue2, temp);
            }
        }
        else
        {
            queue0 = addToQueue(queue0, temp);
        }
    }
}

void *CPU()
{
    int runTime = 0;
    int runCPU = 1;

    while (runCPU == 1)
    {

        pthread_mutex_lock(&lock);
        pthread_cond_wait(&task_avail, &lock); //conditional waiting for the task

        TASK *currTask = getTask();
        pthread_mutex_unlock(&lock);

        if (currTask != NULL)
        {

            int num = rand() % MAXNUM;
            if (currTask->taskType == ioTask && num < currTask->oddsOfIO) // if the tasks is an IO task
            {
                num = rand() % timeSlice;
                currTask->taskLength = currTask->taskLength - num;
                runTime += num;
            }
            else
            {
                // if the current task's length is more than the time slice
                if (currTask->taskLength > timeSlice)
                {
                    // reduce the tasklength by time slice, then the runtime should increrase by timeslice
                    currTask->taskLength = currTask->taskLength - timeSlice;
                    runTime += timeSlice;
                }
                else
                {
                    // if not runtime should increrase by tasklength and set tasklenth to 0
                    runTime += currTask->taskLength;
                    currTask->taskLength = 0;
                }
            }

            //if the task has been completed
            if (currTask->taskLength <= 0)
            {
                pthread_mutex_lock(&lock2);
                update_metrics(currTask->priority, runTime, currTask->taskType);
                pthread_mutex_unlock(&lock2);
            }
            else
            { //return task the running scheduler

                pthread_mutex_lock(&lock);
                returnTask(currTask);
                pthread_mutex_unlock(&lock);
            }
        }

        pthread_mutex_lock(&lock);
        // if all the queues are emepty stop running the cpus
        if (!queue0 && !queue1 && !queue2)
        {
            runCPU = 0;
        }
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

void printMetrics()
{
    printf("\nAverage run time per priority:\n");
    for (int i = 0; i < 3; i++)
    {
        if (countPriority[i] > 0)
            printf("Priority %d average run time: %d\n", i, totalPriorityTime[i] / countPriority[i]);
        else
        {
            printf("Priority %d average run time: %d\n", i, 0);
        }
    }
    printf("\nAverage run time per type:\n");
    for (int i = 0; i < 4; i++)
    {
        if (countType[i] > 0)
            printf("Type %d average run time: %d\n", i, totalTypeTime[i] / countType[i]);
        else
        {
            printf("Type %d average run time: %d\n", i, 0);
        }
    }
}

TASK *getTask()
{
    //provide the task to the CPU according to the policy
    TASK *t = NULL;
    if (policy == PRR)
    {
        t = roundRobin();
    }
    else if (policy == STCF)
    {
        t = SJF();
    }
    else if (policy == MLQ)
    {
        t = MLFQueue();
    }
    if (t)
        run--;
    return t;
}

void returnTask(TASK *t) //task returned to scheduler
{                        //place the task back in the queue
    if (policy == PRR)
    {
        queue0 = addToQueue(queue0, t);
    }
    else if (policy == STCF)
    {

        queue0 = addToQueue(queue0, t);
        queue0 = sortQueue(queue0);
    }
    else
    {

        if (t->priority == 0)
        {
            queue0 = addToQueue(queue0, t);
        }
        else if (t->priority == 1)
        {
            queue1 = addToQueue(queue1, t);
        }
        else
        {
            queue2 = addToQueue(queue2, t);
        }
    }
    run++;
    // if (queue0 || queue1 || queue2)
    // {
    //     // dispatcher();
    // }
}

TASK *SJF()
{ //return shortest task i.e. on the queue head
    node *temp;
    if (queue0)
    {
        temp = queue0;
        queue0 = queue0->next;
        return temp->task;
    }
    return NULL;
}

TASK *roundRobin()
{

    node *temp;
    if (queue0)
    {
        temp = queue0;
        queue0 = queue0->next;
        return temp->task;
    }
    return NULL;
}

TASK *MLFQueue()
{
    //return task from lower queues only if higher queues are empty
    node *temp;
    if (queue0)
    {
        temp = queue0;
        queue0 = queue0->next;
        return temp->task;
    }
    else if (queue1)
    {
        temp = queue1;
        queue1 = queue1->next;
        return temp->task;
    }
    else if (queue2)
    {
        temp = queue2;
        queue2 = queue2->next;
        return temp->task;
    }
    return NULL;
}
