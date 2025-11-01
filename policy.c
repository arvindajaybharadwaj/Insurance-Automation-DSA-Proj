#include "policy.h"

Policy *makePolicy(int policyId, char *policyKind, float premiumAmt, int years, char *policyStatus, float totalCover, float coverLeft)
{
    Policy *newPolicy = (Policy *)malloc(sizeof(Policy));
    if (newPolicy == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newPolicy->policyId = policyId;
    strcpy(newPolicy->policyType, policyKind);
    newPolicy->premium = premiumAmt;
    newPolicy->duration = years;
    strcpy(newPolicy->status, policyStatus);
    newPolicy->totalCoverage = totalCover;
    newPolicy->remainingCoverage = coverLeft;
    newPolicy->next = NULL;
    return newPolicy;
}

Client *findClient(Client *root, int clientId)
{
    if (!root)
        return NULL;
    if (clientId == root->clientId)
        return root;
    else if (clientId < root->clientId)
        return findClient(root->left, clientId);
    else
        return findClient(root->right, clientId);
}

void attachPolicyToClient(Client *clientNode, Policy *policyNode)
{
    if (!clientNode || !policyNode)
        return;
    if (!clientNode->policies)
        clientNode->policies = policyNode;
    else
    {
        Policy *current = clientNode->policies;
        while (current->next)
            current = current->next;
        current->next = policyNode;
    }
}

void insertPolicyToClientTree(Client *root, int clientId, int policyId, char *kind, float premiumAmt, int years, char *status, float totalCover, float coverLeft)
{
    Client *targetClient = findClient(root, clientId);
    if (!targetClient)
    {
        printf("Client with ID %d not found\n", clientId);
        return;
    }
    Policy *newPolicy = makePolicy(policyId, kind, premiumAmt, years, status, totalCover, coverLeft);
    if (newPolicy)
    {
        attachPolicyToClient(targetClient, newPolicy);
        printf("Policy %d successfully added to Client %d\n", policyId, clientId);
    }
}

void printPolicies(Policy *head)
{
    if (!head)
    {
        printf("No policies to display\n");
        return;
    }
    Policy *current = head;
    while (current)
    {
        printf("Policy ID: %d | Type: %s | Premium: %.2f | Duration: %d years | Status: %s\n",
               current->policyId, current->policyType, current->premium, current->duration, current->status);
        printf("Total Coverage: %.2f | Remaining Coverage: %.2f\n",
               current->totalCoverage, current->remainingCoverage);
        printf("-------------------------------------------\n");
        current = current->next;
    }
}
