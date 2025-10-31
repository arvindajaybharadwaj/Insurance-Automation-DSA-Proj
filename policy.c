#include "policy.h"

struct Policy* makePolicy(int policyId, char policyKind[], float premiumAmt, int years, 
                          char policyStatus[], float totalCover, float coverLeft)
{
    struct Policy* newPolicy = (struct Policy*)malloc(sizeof(struct Policy));
    if (newPolicy == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newPolicy->policyID = policyId;
    strcpy(newPolicy->policyType, policyKind);
    newPolicy->premium = premiumAmt;
    newPolicy->duration = years;
    strcpy(newPolicy->status, policyStatus);
    newPolicy->maxCoverage = totalCover;
    newPolicy->remainingCoverage = coverLeft;
    newPolicy->next = NULL;

    return newPolicy;
}

struct Client* findClient(struct Client* root, int clientId)
{
    if (root == NULL)
        return NULL;

    if (clientId == root->customerID)
        return root;
    else if (clientId < root->customerID)
        return findClient(root->left, clientId);
    else
        return findClient(root->right, clientId);
}

void attachPolicyToClient(struct Client* clientNode, struct Policy* policyNode)
{
    if (clientNode == NULL || policyNode == NULL)
        return;

    if (clientNode->policyList == NULL) {
        clientNode->policyList = policyNode;
    } else {
        struct Policy* current = clientNode->policyList;
        while (current->next != NULL)
            current = current->next;
        current->next = policyNode;
    }
}

void insertPolicyToClientTree(struct Client* root, int clientId, int policyId, 
                              char kind[], float premiumAmt, int years, char status[], 
                              float totalCover, float coverLeft)
{
    struct Client* targetClient = findClient(root, clientId);
    if (targetClient == NULL) {
        printf("Client with ID %d not found\n", clientId);
        return;
    }

    struct Policy* newPolicy = makePolicy(policyId, kind, premiumAmt, years, status, totalCover, coverLeft);
    attachPolicyToClient(targetClient, newPolicy);
    printf("Policy %d successfully added to Client %d\n", policyId, clientId);
}

void printPolicies(struct Policy* head)
{
    if (head == NULL) {
        printf("No policies to display\n");
        return;
    }

    struct Policy* current = head;
    while (current != NULL) {
        printf("Policy ID: %d | Type: %s | Premium: %.2f | Duration: %d years | Status: %s\n",
               current->policyID, current->policyType, current->premium, current->duration, current->status);
        printf("Total Coverage: %.2f | Remaining Coverage: %.2f\n", 
               current->maxCoverage, current->remainingCoverage);
        printf("-------------------------------------------\n");
        current = current->next;
    }
}
