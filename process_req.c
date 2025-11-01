#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "process_req.h"

Request *dequeueRequestQueue(RequestQueue *q)
{
    if (!q || !q->front)
    {
        printf("No pending requests.\n");
        return NULL;
    }
    Request *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    temp->next = NULL;
    return temp;
}

Client *searchClient(Client *root, int clientID)
{
    if (!root)
        return NULL;
    if (clientID == root->clientId)
        return root;
    else if (clientID < root->clientId)
        return searchClient(root->left, clientID);
    else
        return searchClient(root->right, clientID);
}

Policy *searchPolicy(Policy *head, int policyID)
{
    while (head)
    {
        if (head->policyId == policyID)
            return head;
        head = head->next;
    }
    return NULL;
}

void handleClaim(Policy *policy)
{
    if (!policy)
        return;
    float claimAmount;
    printf("Enter claim amount for Policy ID %d: ", policy->policyId);
    scanf("%f", &claimAmount);
    if (claimAmount <= policy->remainingCoverage)
    {
        policy->remainingCoverage -= claimAmount;
        printf("Claim successful. Remaining coverage: %.2f\n", policy->remainingCoverage);
    }
    else
    {
        printf("Claim exceeds remaining coverage. Setting remaining coverage to 0.\n");
        policy->remainingCoverage = 0;
    }
    if (policy->remainingCoverage == 0)
        strcpy(policy->status, "exhausted");
    else
        strcpy(policy->status, "active");
}

void handleRenewal(Policy *policy)
{
    if (!policy)
        return;
    int extraDuration;
    printf("Enter additional duration in years for Policy ID %d: ", policy->policyId);
    scanf("%d", &extraDuration);
    policy->duration += extraDuration;
    strcpy(policy->status, "renewed");
    policy->remainingCoverage = policy->totalCoverage;
    printf("Policy renewed. New duration: %d years. Coverage reset to %.2f\n", policy->duration, policy->remainingCoverage);
}

void handleCancellation(Policy *policy)
{
    if (!policy)
        return;
    strcpy(policy->status, "cancelled");
    printf("Policy ID %d marked as cancelled, record retained.\n", policy->policyId);
}

void processNextRequest(RequestQueue *q, Client *root)
{
    Request *req = dequeueRequestQueue(q);
    if (!req)
        return;
    printf("\n=== Processing Request ===\n");
    printf("Request for Client ID %d | Policy ID %d | Type: %s\n", req->clientID, req->policyID, req->type);

    Client *client = searchClient(root, req->clientID);
    if (!client)
    {
        strcpy(req->status, "failed");
        printf("Client not found. Request failed.\n");
        free(req);
        return;
    }

    Policy *policy = searchPolicy(client->policies, req->policyID);
    if (!policy)
    {
        strcpy(req->status, "failed");
        printf("Policy not found. Request failed.\n");
        free(req);
        return;
    }

    if (strcmp(req->type, "claim") == 0)
        handleClaim(policy);
    else if (strcmp(req->type, "renewal") == 0)
        handleRenewal(policy);
    else if (strcmp(req->type, "cancellation") == 0)
        handleCancellation(policy);
    else
    {
        strcpy(req->status, "failed");
        printf("Unknown request type.\n");
        free(req);
        return;
    }
    strcpy(req->status, "fulfilled");
    printf("Request processed successfully.\n");
    free(req);
}
