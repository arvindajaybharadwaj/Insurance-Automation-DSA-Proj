#ifndef POLICY_H
#define POLICY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Policy structure
struct Policy {
    int policyId;
    char policyType[20];
    float premium;
    int duration;
    char status[20];
    float totalCoverage;
    float remainingCoverage;
    struct Policy *next;
};

// Client structure
struct Client {
    int clientId;
    char fullName[50];
    struct Policy *policies;
    struct Client *left;
    struct Client *right;
};

// Function declarations
struct Policy* makePolicy(int policyId, char policyKind[], float premiumAmt, int years, 
                          char policyStatus[], float totalCover, float coverLeft);

struct Client* findClient(struct Client* root, int clientId);

void attachPolicyToClient(struct Client* clientNode, struct Policy* policyNode);

void insertPolicyToClientTree(struct Client* root, int clientId, int policyId, 
                              char kind[], float premiumAmt, int years, char status[], 
                              float totalCover, float coverLeft);

void printPolicies(struct Policy* head);

#endif
