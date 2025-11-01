#include "requests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RequestQueue *createQueue()
{
    RequestQueue *queue = (RequestQueue *)malloc(sizeof(RequestQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueueRequest(RequestQueue *queue, int policyID, int clientID, char *type)
{
    Request *newRequest = (Request *)malloc(sizeof(Request));
    newRequest->policyID = policyID;
    newRequest->clientID = clientID;
    strcpy(newRequest->type, type);
    strcpy(newRequest->status, "PENDING");
    newRequest->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = queue->rear = newRequest;
    }
    else
    {
        queue->rear->next = newRequest;
        queue->rear = newRequest;
    }
}

Request *dequeueRequest(RequestQueue *queue)
{
    if (queue->front == NULL)
        return NULL;
    Request *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    temp->next = NULL;
    return temp;
}

int isQueueEmpty(RequestQueue *queue)
{
    return queue->front == NULL;
}

void displayQueue(RequestQueue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }
    Request *current = queue->front;
    while (current)
    {
        printf("PolicyID: %d, ClientID: %d, Type: %s, Status: %s\n",
               current->policyID, current->clientID, current->type, current->status);
        current = current->next;
    }
}
