typedef struct Policy
{
    int policyID;
    char type[20];
    float premium;
    int duration;
    char status[20];
    float maxCoverage;
    float remainingCoverage;
    struct Policy *next;
} Policy;

typedef struct Client
{
    int clientID;
    char name[50];
    int age;
    char phone[15];
    char email[50];
    Policy *policies;
    struct Client *left;
    struct Client *right;
} Client;

typedef struct Request
{
    int policyID;
    int clientID;
    char type[20];   // "claim", "renewal", "cancellation"
    char status[20]; // "pending", "fulfilled", "failed"
    struct Request *next;
} Request;

typedef struct
{
    Request *front;
    Request *rear;
} RequestQueue;

void enqueue(RequestQueue *q, Request *newReq);
Request *dequeue(RequestQueue *q);

Client *searchClient(Client *root, int clientID);
Policy *searchPolicy(Policy *head, int policyID);

void processNextRequest(RequestQueue *q, Client *root);
void handleClaim(Policy *policy);
void handleRenewal(Policy *policy);
void handleCancellation(Policy *policy);
