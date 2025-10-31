#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H
typedef struct Request {
    int policyID;
    int clientID;
    char type[20];
    char status[20];
    struct Request* next;
} Request;
typedef struct {
    Request* front;
    Request* rear;
} RequestQueue;
RequestQueue* createQueue();
void enqueueRequest(RequestQueue* q, int policyID, int clientID, char* type);
Request* dequeueRequest(RequestQueue* q);
int isQueueEmpty(RequestQueue* q);
void displayQueue(RequestQueue* q);
#endif
