#include "policy.h"

Policy *makePolicy(int policyId, char *policyCode, char *policyKind, float premiumAmt, int years, char *policyStatus, float totalCover, float coverLeft)
{
    Policy *newPolicy = (Policy *)malloc(sizeof(Policy));
    if (newPolicy == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newPolicy->policyId = policyId;
    if (policyCode)
        strncpy(newPolicy->policyCode, policyCode, sizeof(newPolicy->policyCode) - 1);
    newPolicy->policyCode[sizeof(newPolicy->policyCode) - 1] = '\0';
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

void insertPolicyToClientTree(Client *root, int clientId, int policyId, char *policyCode, char *kind, float premiumAmt, int years, char *status, float totalCover, float coverLeft)
{
    Client *targetClient = findClient(root, clientId);
    if (!targetClient)
    {
        printf("Client with ID %d not found\n", clientId);
        return;
    }
    Policy *newPolicy = makePolicy(policyId, policyCode, kind, premiumAmt, years, status, totalCover, coverLeft);
    if (newPolicy)
    {
        attachPolicyToClient(targetClient, newPolicy);
        printf("Policy %s (numeric id: %d) successfully added to Client %d\n", newPolicy->policyCode, policyId, clientId);
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
        printf("Policy Code: %s | Numeric ID: %d | Type: %s | Premium: %.2f | Duration: %d years | Status: %s\n",
               current->policyCode, current->policyId, current->policyType, current->premium, current->duration, current->status);
        printf("Total Coverage: %.2f | Remaining Coverage: %.2f\n",
               current->totalCoverage, current->remainingCoverage);
        printf("-------------------------------------------\n");
        current = current->next;
    }
}
