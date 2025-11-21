#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// All headers for modular files
#include "tree.h"        // BST for client basic info
#include "policy.h"      // Policy and Client struct, policy handling
#include "requests.h"    // Request Queue structure and functions
#include "process_req.h" // Request processing and policy handling

int main()
{
    BST *clientRoot = NULL;                 // BST for basic client info
    struct Client *clientInfoRoot = NULL;   // BST for client policy linkage
    RequestQueue *reqQueue = createQueue(); // Request queue

    int choice;
    while (1)
    {
        printf("\n==== Insurance Management Menu ====\n");
        printf("1. Register new client\n");
        printf("2. Display all clients (BST)\n");
        printf("3. Remove a client (BST)\n");
        printf("4. Add policy to client\n");
        printf("5. Display policies of client\n");
        printf("6. Enqueue new request\n");
        printf("7. Process next request\n");
        printf("8. Display request queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice == 0)
        {
            printf("Exiting...\n");
            break;
        }

        switch (choice)
        {
        case 1:
        {
            if (addBST(&clientRoot))
            {
                printf("Client added to basic BST.\n");
            }
            struct Client *newClient = (struct Client *)malloc(sizeof(struct Client));
            printf("Enter client ID: ");
            scanf("%d", &newClient->clientId);
            printf("Enter client full name: ");
            scanf(" %[^\n]", newClient->fullName);
            newClient->policies = NULL;
            newClient->left = newClient->right = NULL;

            // Insert client info into second BST
            struct Client **cur = &clientInfoRoot, *parent = NULL;
            while (*cur)
            {
                parent = *cur;
                if (newClient->clientId < (*cur)->clientId)
                    cur = &((*cur)->left);
                else if (newClient->clientId > (*cur)->clientId)
                    cur = &((*cur)->right);
                else
                {
                    printf("Client ID already exists in info BST!\n");
                    free(newClient);
                    goto skipInsertClient;
                }
            }
            *cur = newClient;
            printf("Client added to info BST.\n");
        skipInsertClient:
            break;
        }
        case 2:
        {
            printf("==== All Registered Clients ====\n");
            inorderBST(clientRoot);
            break;
        }
        case 3:
        {
            int delId;
            printf("Enter client ID to delete: ");
            scanf("%d", &delId);
            if (removeBST(&clientRoot, delId))
                printf("Client deleted from basic BST.\n");
            // BST removal for clientInfoRoot (not implemented here)
            // For full removal, recursively free policies, etc.
            break;
        }
        case 4:
        {
            int clientId, policyId, years;
            char policyType[20], status[20];
            float premium, totalCover, leftCover;
            printf("Enter client ID for policy: ");
            scanf("%d", &clientId);
            printf("Enter new policy ID: ");
            scanf("%d", &policyId);
            printf("Enter policy type: ");
            scanf("%s", policyType);
            getchar();
            printf("Enter premium amount: ");
            scanf("%f", &premium);
            printf("Enter duration (years): ");
            scanf("%d", &years);
            printf("Enter status: ");
            scanf("%s", status);
            getchar();
            printf("Enter total cover amount: ");
            scanf("%f", &totalCover);
            printf("Enter starting (remaining) cover: ");
            scanf("%f", &leftCover);

            insertPolicyToClientTree(clientInfoRoot, clientId, policyId, policyType, premium, years, status, totalCover, leftCover);
            break;
        }
        case 5:
        {
            int clientId;
            printf("Enter client ID to display policies: ");
            scanf("%d", &clientId);
            struct Client *client = findClient(clientInfoRoot, clientId);
            if (client)
                printPolicies(client->policies);
            else
                printf("Client not found.\n");
            break;
        }
        case 6:
        {
            int clientId, policyId;
            char type[20];
            printf("Enter client ID for request: ");
            scanf("%d", &clientId);
            printf("Enter policy ID for request: ");
            scanf("%d", &policyId);
            printf("Enter request type (claim/renewal/cancellation): ");
            scanf("%s", type);
            getchar();
            enqueueRequest(reqQueue, policyId, clientId, type);
            printf("Request enqueued.\n");
            break;
        }
        case 7:
        {
            processNextRequest(reqQueue, clientInfoRoot);
            break;
        }
        case 8:
        {
            printf("Current request queue:\n");
            displayQueue(reqQueue);
            break;
        }
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    // Clean up memory as necessary here
    return 0;
}
