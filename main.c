#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
            BST *inserted = addBST(&clientRoot);
            if (inserted)
            {
                printf("Client added to basic BST.\n");

                int newClientId = inserted->Id;
                char newClientName[400];
                strcpy(newClientName, inserted->name);

                struct Client *newClient = (struct Client *)malloc(sizeof(struct Client));
                newClient->clientId = newClientId;
                strcpy(newClient->fullName, newClientName);
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
                        break;
                    }
                }
                if (!*cur)
                {
                    *cur = newClient;
                    printf("Client added to info BST.\n");
                }
            }
            else
            {
                // addBST already printed duplicate message
            }
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
            int clientId, years;
            char policyType[20];
            float premium, totalCover, leftCover;
            printf("Enter client ID for policy: ");
            scanf("%d", &clientId);

            struct Client *client = findClient(clientInfoRoot, clientId);
            if (!client)
            {
                printf("Client with ID %d not found.\n", clientId);
                break;
            }

            // Determine next numeric policyId for this client
            int nextPolicyId = 1;
            Policy *pcur = client->policies;
            while (pcur)
            {
                if (pcur->policyId >= nextPolicyId)
                    nextPolicyId = pcur->policyId + 1;
                pcur = pcur->next;
            }

            // Generate a short prefix from client name (letters only, lowercased)
            char prefix[8] = {0};
            int pi = 0;
            for (int i = 0; client->fullName[i] != '\0' && pi < 6; ++i)
            {
                char c = client->fullName[i];
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                {
                    if (c >= 'A' && c <= 'Z')
                        c = c - 'A' + 'a';
                    prefix[pi++] = c;
                }
            }
            if (pi > 3)
                prefix[3] = '\0';
            if (pi == 0)
                strcpy(prefix, "usr");

            char policyCode[64];
            snprintf(policyCode, sizeof(policyCode), "%s%d%d", prefix, clientId, nextPolicyId);

            // Prompt for policy type and validate against allowed list
            const char *allowedTypes[] = {"life", "home", "vehicle"};
            int typeValid = 0;
            while (!typeValid)
            {
                printf("Enter policy type (life/home/vehicle): ");
                if (scanf("%19s", policyType) != 1)
                {
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                char lower[20];
                int i;
                for (i = 0; policyType[i] && i < (int)sizeof(lower) - 1; ++i)
                    lower[i] = (char)tolower((unsigned char)policyType[i]);
                lower[i] = '\0';

                for (int j = 0; j < 3; ++j)
                {
                    if (strcmp(lower, allowedTypes[j]) == 0)
                    {
                        // normalize stored policyType to lowercase allowed value
                        strcpy(policyType, allowedTypes[j]);
                        typeValid = 1;
                        break;
                    }
                }
                if (!typeValid)
                    printf("Invalid policy type. Please enter one of: life, home, vehicle.\n");
            }
            printf("Enter premium amount: ");
            scanf("%f", &premium);
            printf("Enter duration (years): ");
            scanf("%d", &years);
            char status[20] = "active";
            getchar();
            printf("Enter total cover amount: ");
            scanf("%f", &totalCover);
            leftCover = totalCover;

            insertPolicyToClientTree(clientInfoRoot, clientId, nextPolicyId, policyCode, policyType, premium, years, status, totalCover, leftCover);
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

            struct Client *clientReq = findClient(clientInfoRoot, clientId);
            if (!clientReq)
            {
                printf("Client with ID %d not found.\n", clientId);
                break;
            }

            // Display active and renewed policies for this client
            Policy *pp = clientReq->policies;
            int shown = 0;
            printf("Available policies for client %d:\n", clientId);
            while (pp)
            {
                if (strcmp(pp->status, "active") == 0 || strcmp(pp->status, "renewed") == 0)
                {
                    printf("Policy Code: %s | Numeric ID: %d | Type: %s | Status: %s | Remaining: %.2f\n",
                           pp->policyCode, pp->policyId, pp->policyType, pp->status, pp->remainingCoverage);
                    shown = 1;
                }
                pp = pp->next;
            }
            if (!shown)
            {
                printf("No active or renewed policies available for client %d.\n", clientId);
                break;
            }

            printf("Enter policy ID for request: ");
            scanf("%d", &policyId);

            // Validate request type: accept claim / renew / cancel (map to expected strings)
            int valid = 0;
            while (!valid)
            {
                printf("Enter request type (claim/renew/cancel): ");
                if (scanf("%19s", type) != 1)
                {
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                char lower[20];
                int i;
                for (i = 0; type[i] && i < (int)sizeof(lower) - 1; ++i)
                    lower[i] = (char)tolower((unsigned char)type[i]);
                lower[i] = '\0';

                if (strcmp(lower, "claim") == 0)
                {
                    strcpy(type, "claim");
                    valid = 1;
                }
                else if (strcmp(lower, "renew") == 0 || strcmp(lower, "renewal") == 0)
                {
                    strcpy(type, "renewal");
                    valid = 1;
                }
                else if (strcmp(lower, "cancel") == 0 || strcmp(lower, "cancellation") == 0)
                {
                    strcpy(type, "cancellation");
                    valid = 1;
                }
                else
                {
                    printf("Invalid request type. Please enter one of: claim, renew, cancel.\n");
                }
            }

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
