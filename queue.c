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

node *newNode(task *task)
{
    node *temp = (node *)malloc(sizeof(queue));
    temp->task = task;
    temp->next = NULL;
    return temp;
}

node *addToQueue(node *head, task *task)
{

    node *new_task = newNode(task);

    // if queue is empty
    if (head == NULL)
    {
        head = new_task;
    }
    else
    {
        node *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new_task;
    }

    return head;
}

node *sortQueue(node *head)
{
    node *current = head;
    node *index = NULL;
    task *temp = NULL;

    if (head != NULL)
    {
        while (current != NULL)
        {
            //Node index will point to node next to current
            index = current->next;

            while (index != NULL)
            {
                //If current node's data is greater than index's node data, swap the data between them
                if (current->task->task_length > index->task->task_length)
                {
                    //swap
                    temp = current->task;
                    current->task = index->task;
                    index->task = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    return head;
}