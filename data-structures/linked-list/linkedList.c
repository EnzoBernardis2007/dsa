#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define what is a Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

int countList(Node** head) {
    Node* temp = *head;
    int count = 0;

    while(temp != NULL) {
        temp = temp->next;
        count++;
    }

    return count;
}

Node* createNode(int value) {
    // Allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL) {
        printf("Error trying allocate memory\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int value) {
    Node* newNode = createNode(value); // Create a new node
    newNode->next = *head; // Define next node of the new node as the head
    *head = newNode; // And finally define the new node as the head
}

void insertAtEnd(Node** head, int value) {
    Node* newNode = createNode(value); // Create a new node

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head; // Get the head

    while(temp->next != NULL) {
        temp = temp->next; // Reach the final node
    }

    temp->next = newNode; // Set the next of the final node as the new node
}

void insertAt(Node** head, int position, int value) {
    Node* newNode = createNode(value);
    Node* temp = *head, *prev = NULL;

    if(*head == NULL) {
        newNode->next = *head;
        *head = newNode;
        return;
    } else if(countList(head) <= position) {
        printf("Position out of length");
        return;
    }

    int actualPosition = 0;

    while(actualPosition != position) {
        actualPosition++;
        prev = temp;
        temp = temp->next;
    }

    prev->next = newNode;
    newNode->next = temp;
}

void deleteNode(Node** head, int value) {
    Node* temp = *head, *prev = NULL;

    if(temp != NULL && temp->data == value) {
        *head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("value %d as not found\n", value);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void deleteNodeAt(Node** head, int position) {
    Node* temp = *head, *prev = NULL;
    int actualPosition = 0;

    if(position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while(actualPosition != position) {
        actualPosition++;
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
}

void freeList(Node* head) {
    Node* temp;
    
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void showList(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        printf("%d -> ", temp->data); // Print the value of the actual node
        temp = temp->next; // Define the temp as the next node
    }

    printf("NULL\n");
}

bool containValue(Node** head, int value) {
    Node* temp = *head;

    while(temp != NULL) {
        if(temp->data == value) {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void makeItCircular(Node** givenHead) {
    Node* head = *givenHead;
    Node* temp = head;

    while(temp->next != NULL){
        temp = temp->next;
    }
    
    temp->next = head;
}

void concatLists(Node** head1, Node** head2) {
    Node* temp = *head1;

    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = *head2;
}

Node* copyList(Node** head) {
    Node* temp = *head;
    Node* newHead = createNode(temp->data);
    Node* newList = newHead;

    temp = temp->next;

    while(temp != NULL) {
        newList->next = createNode(temp->data);
        newList = newList->next;
        temp = temp->next;
    }

    return newHead;
}

Node* revertList(Node* head) {
    if(head == NULL || head->next == NULL) {
        return head;
    }

    Node* newHead = revertList(head->next);
    head->next->next = head;
    head->next = NULL;

    return newHead;
}

int main() {
    Node* head1 = createNode(3);

    insertAtBeginning(&head1, 1);
    insertAtEnd(&head1, 4);
    insertAt(&head1, 1, 2);

    showList(head1);

    Node* head2 = NULL;
    for (int i = 1; i <= 5; i++) {
        insertAtEnd(&head2, i);
    }
    Node* head3 = copyList(&head2);

    deleteNode(&head2, 4);
    deleteNodeAt(&head2, 1);

    showList(head2);

    head3 = revertList(head3);
    showList(head3);

    concatLists(&head2, &head3);

    showList(head2);

    freeList(head1);
    freeList(head2);
    freeList(head3);
    
    return 0;
}