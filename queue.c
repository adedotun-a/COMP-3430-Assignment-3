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

struct QNode
{
    task *task;
    struct QNode *next;
};

node *newNode(task *task)
{
    node *temp = (node *)malloc(sizeof(node));
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
    // else if queue is not empty
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

// bubble sort the queue for STCF
node *sortQueue(node *head)
{
    node *prev = head;
    node *curr = NULL;
    task *temp = NULL;

    if (head != NULL)
    {
        while (prev != NULL)
        {
            //The curr node points to the node after prev
            curr = prev->next;

            while (curr != NULL)
            {
                //If previous node's task_length is greater than current node's task_length, swap the tasks
                if (prev->task->taskLength > curr->task->taskLength)
                {
                    //swap
                    temp = prev->task;
                    prev->task = curr->task;
                    curr->task = temp;
                }
                curr = curr->next;
            }
            prev = prev->next;
        }
    }

    return head;
}