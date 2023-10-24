#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    char data;
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
void insert(struct Node* sentinel, char data, int priority) {
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
char dequeue_max(struct Node* sentinel) {
    if (sentinel->next == sentinel) {
        printf("Queue is empty\n");
        return 0; // Empty queue
    }
    
    char info;

    // Find the node with the highest priority
    struct Node* maxPriorityNode = sentinel->next;
    info = maxPriorityNode->data;
    struct Node* temp = sentinel->next->next;
    
    while (temp != sentinel) {
        if (temp->priority >= maxPriorityNode->priority) {
            maxPriorityNode = temp;
            info = maxPriorityNode->data;
        }
        temp = temp->next;
    }

    // Remove the node from the list
    maxPriorityNode->prev->next = maxPriorityNode->next;
    maxPriorityNode->next->prev = maxPriorityNode->prev;

    printf("Succesfully dequeued max\n");
    free(maxPriorityNode);

    return info;
}

char dequeue(struct Node* sentinel) {
    // checks for empty queue
    if (sentinel->next == sentinel) {
        printf("Queue is empty\n");
        return 0;
    }
    struct Node* temp = sentinel->next;

    // prio variable to store node values in
    char info;

    // removes node nearest head from queue while recording its data
    info = temp->data;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    // frees removed node and prints success statement
    free(temp);
    printf("succesfully dequeued\n");

    return info;
}

int main() {
    struct Node* sentinel = initializePriorityQueue();
    
    insert(sentinel, '1', 3);
    insert(sentinel, '2', 1);
    insert(sentinel, '3', 4);
    insert(sentinel, '4', 2);
    insert(sentinel, '7', 4);
    
    printf("Data: %c\n", dequeue_max(sentinel));

    while (sentinel->next != sentinel) {
        printf("Data: %c\n", dequeue(sentinel));
    }

    // Free the sentinel node
    free(sentinel);
    
    return 0;
}
