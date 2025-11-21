#ifndef POLICY_H
#define POLICY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Policy
{
    int policyId;
    char policyCode[64];
    char policyType[20];
    float premium;
    int duration;
    char status[20];
    float totalCoverage;
    float remainingCoverage;
    struct Policy *next;
};
typedef struct Policy Policy;

struct Client
{
    int clientId;
    char fullName[50];
    Policy *policies;
    struct Client *left;
    struct Client *right;
};
typedef struct Client Client;

Policy *makePolicy(int policyId, char *policyCode, char *policyKind, float premiumAmt, int years, char *policyStatus, float totalCover, float coverLeft);
Client *findClient(Client *root, int clientId);
void attachPolicyToClient(Client *clientNode, Policy *policyNode);
void insertPolicyToClientTree(Client *root, int clientId, int policyId, char *policyCode, char *kind, float premiumAmt, int years, char *status, float totalCover, float coverLeft);
void printPolicies(Policy *head);

#endif
