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
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"

#define MAXNUM 100

//Variables
int count_type[4] = {0, 0, 0, 0};
int count_priority[3] = {0, 0, 0};

int avg_type_time[4] = {0, 0, 0, 0};
int avg_priority_time[3] = {0, 0, 0};

int policy;
int timeSlice = MAXNUM;

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

// main
int main(int argc, char *argv[])
{
    if (argc < 3) //Check if commandline arguments are valid
    {
        printf("The no of CPUs and chosen scheduling policy are missing\n");
        return -1;
    }

    int num_of_cores = atoi(argv[1]);
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
        printf("Enter valid policy\n");
        return -1;
    }
}

void update_metrics(int priority, int time, taskType type)
{
    //update metric arrays
    count_type[type] += 1;
    count_priority[type] += 1;
    avg_type_time[type] += time;
    avg_priority_time[priority] += time;
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

void initQueue(char *filename)
{
    char buffer[MAXNUM];
    char *data[6];
    FILE *file;
    char path[3 + strlen(filename)];
    strcpy(path, "./");
    strcat(path, filename);
    file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    // while (fgets(buffer, MAXNUM, file) != NULL)
    // {
    //     task *temp = malloc(sizeof(task));

    //     strcpy(temp->taskName, strtok(buffer, " "));
    //     temp->taskType = atoi(strtok(NULL, " "));
    //     temp->priority = atoi(strtok(NULL, " "));
    //     temp->taskLength = atoi(strtok(NULL, " "));
    //     temp->oddsOfIO = atoi(strtok(NULL, "\n"));

    //     if (policy == MLQ)
    //     {
    //         if (temp->priority == 0)
    //         {
    //             queue0 = addToReadyQ(queue0, temp);
    //         }
    //         else if (temp->priority == 1)
    //         {
    //             queue1 = addToReadyQ(queue1, temp);
    //         }
    //         else
    //         {
    //             queue2 = addToReadyQ(queue2, temp);
    //         }
    //     }
    //     else
    //     {
    //         queue0 = addToReadyQ(queue0, temp);
    //     }
    // }
    task *temp = malloc(sizeof(task));
    while (fscanf(file, "%s %d %d %d %d\n", temp->taskName, temp->taskType, temp->priority, temp->taskLength, temp->oddsOfIO))
    {
        if (policy == MLQ)
        {
            if (temp->priority == 0)
            {
                queue0 = addToReadyQ(queue0, temp);
            }
            else if (temp->priority == 1)
            {
                queue1 = addToReadyQ(queue1, temp);
            }
            else
            {
                queue2 = addToReadyQ(queue2, temp);
            }
        }
        else
        {
            queue0 = addToReadyQ(queue0, temp);
        }
    }
}

void *CPU()
{
    int runTime = 0;
    int run = 1;

    while (run == 1)
    {

        pthread_mutex_lock(&lock);
        pthread_cond_wait(&task_avail, &lock); //conditional waiting for the task

        task *currTask = getTask();
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
            run = 0;
        }
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}