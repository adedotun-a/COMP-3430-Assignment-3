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
