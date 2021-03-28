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

//Variables
int count_type[4] = {0, 0, 0, 0};
int count_priority[3] = {0, 0, 0};

int avg_type_time[4] = {0, 0, 0, 0};
int avg_priority_time[3] = {0, 0, 0};

int policy;

node *queue0; //highest queue (priority 2)
node *queue1; //medium priority queue
node *queue2; //low priority queue

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

void update_metrics(metrics s)
{
    //update metric arrays
    count_type[s.type] += 1;
    count_priority[s.type] += 1;
    avg_type_time[s.type] += s.time;
    avg_priority_time[s.priority] += s.time;
}

void *dispatcher()
{ //alert the CPUs that a task is available
    int flag = 1;
    while (flag == 1)
    {
        pthread_mutex_lock(&lock);

        pthread_cond_signal(&task_avail);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

void populate(Queue *arr)
{

    char info[50];
    char *data[6];
    FILE *fp = fopen("process_config.txt", "r");
    if (fp == NULL)
    {
        printf("file open failed\n");
        exit(1);
    }
    else
    {
        int count = 0;
        while ((fgets(info, 50, fp) != NULL) && (size(arr) < getLimit(arr)))
        {
            count++;
            char *tok = strtok(info, " \n");
            int i = 0;
            while (tok != NULL)
            {
                data[i++] = tok;
                tok = strtok(NULL, " \n");
            }
            process *newProc = (process *)malloc(sizeof(process));
            newProc->name = (char *)malloc(sizeof(char) * 10);
            strcpy(newProc->name, data[0]);
            newProc->type = atoi(data[1]);
            newProc->pty = atoi(data[2]);
            newProc->runTime = atoi(data[3]);
            newProc->max_runTime = atoi(data[3]);
            newProc->startTime = atoi(data[4]);
            newProc->ioPercent = atoi(data[5]);
            queuePty(arr, newProc, "startTime");
            count_type[newProc->type]++;
            count_priority[newProc->pty]++;
        }
    }
}

void initQueue(char *filename)
{
    // int in = 0;
    FILE *file;
    // int bufferSize = 100;
    // char buffer[bufferSize];
    char path[3 + strlen(filename)];
    strcpy(path, "./");
    strcat(path, filename);
    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1)
    {

        task *temp = malloc(sizeof(task));

        strcpy(temp->task_name, strtok(line, " "));
        temp->taskType = atoi(strtok(NULL, " "));
        temp->priority = atoi(strtok(NULL, " "));
        temp->task_length = atoi(strtok(NULL, " "));
        temp->odds_of_IO = atoi(strtok(NULL, "\n"));

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