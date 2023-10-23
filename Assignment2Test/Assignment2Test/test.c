#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    int priority;
    struct Node* next;
    struct Node* prev;
};

// Initialize an empty priority queue with a sentinel node
struct Node* initializePriorityQueue() {
    struct Node* sentinel = (struct Node*)malloc(sizeof(struct Node));
    sentinel->data = 0;
    sentinel->priority = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    return sentinel;
}

// Insert a new node into the priority queue
void insert(struct Node* sentinel, int data, int priority) {
    // Allocate memory for the new node and set its data and priority
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;

    // Insert the new node after the sentinel
    newNode->next = sentinel->next;
    newNode->prev = sentinel;
    sentinel->next->prev = newNode;
    sentinel->next = newNode;
}

// Remove and return the node with the highest priority
struct Node* dequeue(struct Node* sentinel) {
    if (sentinel->next == sentinel) {
        return NULL; // Empty queue
    }
    
    // Find the node with the highest priority
    struct Node* maxPriorityNode = sentinel->next;
    struct Node* temp = sentinel->next->next;
    while (temp != sentinel) {
        if (temp->priority > maxPriorityNode->priority) {
            maxPriorityNode = temp;
        }
        temp = temp->next;
    }

    // Remove the node from the list
    maxPriorityNode->prev->next = maxPriorityNode->next;
    maxPriorityNode->next->prev = maxPriorityNode->prev;
    
    return maxPriorityNode;
}

int main() {
    struct Node* sentinel = initializePriorityQueue();
    
    insert(sentinel, 1, 3);
    insert(sentinel, 2, 1);
    insert(sentinel, 3, 4);
    insert(sentinel, 4, 2);
    
    struct Node* maxNode = dequeue(sentinel);
    while (maxNode != NULL) {
        printf("Data: %d, Priority: %d\n", maxNode->data, maxNode->priority);
        free(maxNode);
        maxNode = dequeue(sentinel);
    }
    
    // Free the sentinel node
    free(sentinel);
    
    return 0;
}
