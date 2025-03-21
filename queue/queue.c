#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if(q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q) {
    if(q->front == NULL) {
        return -1;
    }

    Node* temp = q->front;

    q->front = q->front->next;

    if(q->front == NULL) {
        q->rear = NULL;
    }

    int data = temp->data;
    free(temp);

    return data;
}

void show(Queue* q) {
    Node* temp = q->front;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int peek(Queue* q) {
    return q->front->data;
}

int size(Queue* q) {
    Node* temp = q->front;
    int count = 0;

    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

Queue* copyQueue(Queue* q) {
    Node* temp = q->front;
    Queue* newQueue = createQueue();

    while(temp != NULL) {
        enqueue(newQueue, temp->data);
        temp = temp->next;
    }

    return newQueue;
}

void reverse(Queue* q) {
    if (q->front == NULL) {
        return;
    }

    int data = dequeue(q);
    reverse(q);
    enqueue(q, data);
}

int main() {
    Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    reverse(queue);
    show(queue);
    return 0;
}