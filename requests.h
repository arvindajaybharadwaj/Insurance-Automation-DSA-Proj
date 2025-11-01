#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

struct Request
{
    int policyID;
    int clientID;
    char type[20];
    char status[20];
    struct Request *next;
};
typedef struct Request Request;

struct RequestQueue
{
    Request *front, *rear;
};
typedef struct RequestQueue RequestQueue;

RequestQueue *createQueue();
void enqueueRequest(RequestQueue *q, int policyID, int clientID, char *type);
Request *dequeueRequest(RequestQueue *q);
int isQueueEmpty(RequestQueue *q);
void displayQueue(RequestQueue *q);

#endif
