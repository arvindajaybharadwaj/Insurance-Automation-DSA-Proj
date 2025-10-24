# Insurance Automation Software for DSA Sem 3

## Requirement #1

Client Operations (adding, deleting, and displaying clients)

### Description:

We take details of client (Name, ID, age, phone number, email) and use a binary
search tree to place the client based on their ID with a pointer to a linked list of
policies of the client. Deleting the client and displaying all the clients becomes easy
and is order.

### Category: Easy

### Justification:

Adding a client to a binary search tree is easy as it is simple insertion to a bst.
Deleting is little harder as it involves freeing up policy linked list, but is still easy
overall. Displaying clients in bst in order of their ID becomes easy in bst.

## Requirement #2

Request Submissions (claim, renewal, or cancellation of a policy)

### Description:

Each request is stored in a queue based on the order they are filed in. Each request
is also a struct with the properties of policy ID, client ID, type, status(pending,
fulfilled, failed), and next pointer.

### Category: Easy

### Justification:

Request submission is easy as it involves doing simple enqueue to a queue data
structure that can be implemented with either singly linked lists or an array. Each
request node should be created with its struct which is also easy.

## Requirement #3

Adding a Policy

### Description:

We take customer ID, policy ID, policy type (Health, Vehicle, Life), premium amount,
duration, status, max coverage, remaining coverage, and pointer to the next policy.
This policy created is then added to the policy linked list contained in each client
node in the binary search tree.

### Category: Not so easy

### Justification:

Classified this as not so easy because it involves traversing two data structures, both
a binary search tree and a policy linked list in order to add a new policy to an existing
client.

## Requirement #4

Processing Requests

### Description:

When this option is chosen, we dequeue the next pending request from the request
queue and handle the request. Based on the type of request, they are handled
differently. Claim requests update the policy’s remaining coverage and status if
required, renewal requests update the policy’s duration and status, and cancellation
updates the status of the policy but does not delete it to maintain history of policies
for each client

### Category: Not so easy

### Justification:

This not only involves searching for each client in the bst, but also involves
traversing the policies linked list, searching for the correct policy with the policy ID,
and then updating the respective policy. This makes this requirement not so easy.
