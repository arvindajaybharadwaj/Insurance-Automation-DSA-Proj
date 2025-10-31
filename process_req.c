#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process_req.h"

// Dequeue a request from the front of the queue
Request *dequeue(RequestQueue *q)
{
    if (!q || q->front == NULL)
    {
        printf("No pending requests.\n");
        return NULL;
    }

    Request *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    temp->next = NULL; // detach
    return temp;
}

// ==================== SEARCH HELPERS ====================

// Search for a client in the BST by clientID
Client *searchClient(Client *root, int clientID)
{
    if (root == NULL)
        return NULL;

    if (clientID == root->clientID)
        return root;
    else if (clientID < root->clientID)
        return searchClient(root->left, clientID);
    else
        return searchClient(root->right, clientID);
}

// Search for a policy by policyID in the client's linked list
Policy *searchPolicy(Policy *head, int policyID)
{
    while (head)
    {
        if (head->policyID == policyID)
            return head;
        head = head->next;
    }
    return NULL;
}

// ==================== POLICY HANDLERS ====================

// Claim request: reduce remaining coverage
void handleClaim(Policy *policy)
{
    if (!policy)
        return;
    float claimAmount;
    printf("Enter claim amount for Policy ID %d: ", policy->policyID);
    scanf("%f", &claimAmount);

    if (claimAmount <= policy->remainingCoverage)
    {
        policy->remainingCoverage -= claimAmount;
        printf("✔ Claim successful. Remaining coverage: %.2f\n", policy->remainingCoverage);
    }
    else
    {
        printf("⚠ Claim exceeds remaining coverage. Setting remaining coverage to 0.\n");
        policy->remainingCoverage = 0;
    }

    if (policy->remainingCoverage == 0)
        strcpy(policy->status, "exhausted");
    else
        strcpy(policy->status, "active");
}

// Renewal request: extend duration
void handleRenewal(Policy *policy)
{
    if (!policy)
        return;
    int extraDuration;
    printf("Enter additional duration (in months/years) for Policy ID %d: ", policy->policyID);
    scanf("%d", &extraDuration);

    policy->duration += extraDuration;
    strcpy(policy->status, "renewed");
    policy->remainingCoverage = policy->maxCoverage;

    printf("✔ Policy renewed. New duration: %d | Coverage reset to %.2f\n",
           policy->duration, policy->remainingCoverage);
}

// Cancellation request: mark as cancelled but do not delete
void handleCancellation(Policy *policy)
{
    if (!policy)
        return;
    strcpy(policy->status, "cancelled");
    printf("✔ Policy ID %d marked as cancelled (record retained).\n", policy->policyID);
}

// ==================== REQUEST PROCESSING ====================

void processNextRequest(RequestQueue *q, Client *root)
{
    Request *req = dequeue(q);
    if (!req)
        return;

    printf("\nProcessing Request for Client ID: %d | Policy ID: %d | Type: %s\n",
           req->clientID, req->policyID, req->type);

    Client *client = searchClient(root, req->clientID);
    if (!client)
    {
        strcpy(req->status, "failed");
        printf("Client not found. Request failed.\n");
        return;
    }

    Policy *policy = searchPolicy(client->policies, req->policyID);
    if (!policy)
    {
        strcpy(req->status, "failed");
        printf("Policy not found. Request failed.\n");
        return;
    }

    if (strcmp(req->type, "claim") == 0)
    {
        handleClaim(policy);
    }
    else if (strcmp(req->type, "renewal") == 0)
    {
        handleRenewal(policy);
    }
    else if (strcmp(req->type, "cancellation") == 0)
    {
        handleCancellation(policy);
    }
    else
    {
        strcpy(req->status, "failed");
        printf("Unknown request type.\n");
        return;
    }

    strcpy(req->status, "fulfilled");
    printf("Request processed successfully.\n");
}