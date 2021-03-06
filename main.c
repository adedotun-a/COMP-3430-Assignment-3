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

node *queue0; //priority 0 queue (high)
node *queue1; //priority 1  queue (med)
node *queue2; //priority 2 squeue (low)

//declaring condition variables
pthread_cond_t availableTask = PTHREAD_COND_INITIALIZER;
pthread_cond_t cpu_avail = PTHREAD_COND_INITIALIZER;
// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void initQueue();
void *CPU();
void printMetrics();
TASK *getNextTask();
void returnToQueue(TASK *t);
// TASK *SJF();
TASK *defaultDeQueue();
TASK *MLFDeQueue();
void *dispatcher();

// main
int main(int argc, char *argv[])
{
    if (argc < 2) //Check if commandline arguments are valid
    {
        printf("Please enter the chosen scheduling policy\n");
        return -1;
    }
    if (argc < 3) //Check if commandline arguments are valid
    {
        printf("Please enter the no of CPUs and chosen scheduling policy\n");
        return -1;
    }

    int numCores = atoi(argv[1]);
    if (strcmp(argv[2], "rr") == 0)
    {
        policy = PRR;
        printf("Using pure round-robin with %d CPUs.\n", numCores);
    }
    else if (strcmp(argv[2], "stcf") == 0)
    {
        policy = STCF;
        printf("Using shortest time to completion first with %d CPUs.\n", numCores);
    }
    else if (strcmp(argv[2], "mlfq") == 0)
    {
        policy = MLQ;
        printf("Using the multi-level feedback queue with %d CPUs.\n", numCores);
    }
    else
    {
        printf("Please enter a valid policy\n");
        return -1;
    }

    initQueue();
    // numCores += 0;
    pthread_t *pIds = malloc(sizeof(pthread_t) * numCores);
    for (int i = 0; i < numCores; i++) //create threads for CPUS
    {
        pthread_create(&pIds[i], NULL, CPU, NULL);
    }

    pthread_t tid1;

    pthread_create(&tid1, NULL, dispatcher, NULL); //create thread that runs the scheduler
    for (int i = 0; i < numCores; i++)
    {
        pthread_join(pIds[i], NULL);
    }
    printMetrics();
}

void updateMetrics(int priority, int time, taskType type)
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

        pthread_cond_signal(&availableTask);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

void initQueue()
{
    // read the fil and initialize the queue
    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL)
    {
        printf("I/O Error, unable to open file!\n");
        exit(1);
    }

    TASK *temp = malloc(sizeof(TASK));
    while (fscanf(file, "%s %d %d %d %d\n", temp->taskName, &(temp->taskType), &(temp->priority), &(temp->taskLength), &(temp->oddsOfIO)) == 5)
    {
        temp = malloc(sizeof(TASK));
        if (policy == MLQ)
        {
            if (temp->priority == 0)
            {
                queue0 = enQueue(queue0, temp);
            }
            else if (temp->priority == 1)
            {
                queue1 = enQueue(queue1, temp);
            }
            else
            {
                queue2 = enQueue(queue2, temp);
            }
        }
        else
        {
            queue0 = enQueue(queue0, temp);
        }
    }
    fclose(file);
}

void *CPU()
{
    int runTime = 0;
    int runCPU = 1;

    while (runCPU == 1)
    {

        pthread_mutex_lock(&lock);
        pthread_cond_wait(&availableTask, &lock); //conditional waiting for the task

        TASK *currTask = getNextTask();

        pthread_mutex_unlock(&lock);

        if (currTask != NULL)
        {
            int randInt = rand() % MAXNUM;
            if (currTask->taskType == ioTask && randInt < currTask->oddsOfIO) // if the tasks is an IO task
            {
                randInt = rand() % timeSlice;
                currTask->taskLength -= randInt;
                runTime += randInt;
            }
            else
            {
                // if the current task's length is more than the time slice
                if (currTask->taskLength > timeSlice)
                {
                    // reduce the tasklength by time slice, then the runtime should increrase by timeslice
                    currTask->taskLength -= timeSlice;
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
                updateMetrics(currTask->priority, runTime, currTask->taskType);
                pthread_mutex_unlock(&lock2);
            }
            else
            { //return task the running scheduler

                pthread_mutex_lock(&lock);
                returnToQueue(currTask);
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

TASK *getNextTask()
{
    //provide the next avaialable task to the using the approipraite dequeue method
    TASK *t = NULL;
    if (policy == PRR)
    {
        t = defaultDeQueue();
    }
    else if (policy == STCF)
    {
        t = defaultDeQueue();
    }
    else if (policy == MLQ)
    {
        t = MLFDeQueue();
    }
    return t;
}

void returnToQueue(TASK *t) // return a task back in the queue
{
    // if the policy is PRR then place the tasks default queue (queue0)
    if (policy == PRR)
    {
        queue0 = enQueue(queue0, t);
    }
    // if the policy is STCF then place the tasks default queue (queue0), then sort the queue
    else if (policy == STCF)
    {

        queue0 = enQueue(queue0, t);
        queue0 = sortQueue(queue0);
    }
    else
    {
        // if the policy is MLFQ then place the tasks in their appriopriate queues
        if (t->priority == 0)
        {
            queue0 = enQueue(queue0, t);
        }
        else if (t->priority == 1)
        {
            queue1 = enQueue(queue1, t);
        }
        else
        {
            queue2 = enQueue(queue2, t);
        }
    }
}

// dequeue method for PRR and STCF
TASK *defaultDeQueue()
{
    // remove the task at the top of the queue
    node *temp;
    if (queue0)
    {
        temp = queue0;
        queue0 = queue0->next;
        return temp->task;
    }
    return NULL;
}

// dequeue method for MLF
TASK *MLFDeQueue()
{
    //return task from lower priority queues if higher priority queues are empty
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
