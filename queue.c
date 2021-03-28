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

typedef struct QNode
{
    task *task;
    struct QNode *next;
} node;

struct QNode *newNode(task *task)
{
    struct QNode *temp = (node *)malloc(sizeof(queue));
    temp->task = task;
    temp->next = NULL;
    return temp;
}

node *addToQueue(node *head, task *task)
{

    node *curr = head;
    node *new_task = (node *)malloc(sizeof(queue));
    new_task->task = task;
    new_task->next = NULL;

    // if queue is empty
    if (head == NULL)
    {
        head = new_task;
    }
    else
    {
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = new_task;
    }

    return head;
}