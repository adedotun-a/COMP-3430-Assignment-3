/*
* COURSE: COMP 3340 SECTION [A02]
* INSTRUCTOR: Rasit Eskicioglu
* NAME: Adedotun Adeyemo
* STUDENT ID: 7784807
* ASSIGNMENT: 3
* QUESTION: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct QUEUE
{
    task *t;
    struct QUEUE *next;
} queue;

queue *addToQueue(queue *head, task *t)
{

    queue *current = head;
    queue *new_task = (queue *)malloc(sizeof(queue));
    new_task->t = t;
    new_task->next = NULL;

    if (head == NULL)
    {

        head = new_task;

        return head;
    }

    while (current->next)
    {
        current = current->next;
    }
    current->next = new_task;

    return head;
}