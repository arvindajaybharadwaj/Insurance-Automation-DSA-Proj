#ifndef PROCESSREQ_H
#define PROCESSREQ_H

#include "requests.h"
#include "policy.h"

void enqueueRequestQueue(RequestQueue *q, Request *newReq);
Request *dequeueRequestQueue(RequestQueue *q);

Client *searchClient(Client *root, int clientID);
Policy *searchPolicy(Policy *head, int policyID);

void processNextRequest(RequestQueue *q, Client *root);
void handleClaim(Policy *policy);
void handleRenewal(Policy *policy);
void handleCancellation(Policy *policy);

#endif
