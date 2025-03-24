#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node {
    char data;
    int count;
    struct Node* next[MAX];
} Node;

Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL) return NULL;

    newNode->data = value;
    newNode->count = 0;

    for(int i = 0; i < MAX; i++) {
        newNode->next[i] = NULL;
    }

    return newNode;
}

void addNode(Node *root, int count, ...) {
    if(root == NULL) {
        return;
    }

    va_list args;
    va_start(args, count);

    for(int i = 0; i < count ; i++) {
        if(root->count >= MAX) {
            break;
        }

        root->next[root->count] = createNode(va_arg(args, int));
        root->count++;
    }

    va_end(args);
}

void show(Node *root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%c\n", root->data);

    for (int i = 0; i < root->count; i++) {
        show(root->next[i], level + 1);
    }
}

int size(Node* root) {
    if(root == NULL) return 0;

    int total = 1;

    for(int i = 0; i < root->count; i++) {
        total += size(root->next[i]);
    }

    return total;
}

bool hasValue(Node* root, char value) {
    if(root == NULL) return false;

    if(root->data == value) {
        return true;
    }

    for(int i = 0; i < root->count; i++) {
        if(hasValue(root->next[i], value)) {
            return true;
        } 
    }

    return false;
}

int height(Node* root) {
    if(root == NULL) return -1;

    int maxHeight = 0;

    for(int i = 0; i < root->count; i++) {
        int childHeight = height(root->next[i]);

        if(childHeight > maxHeight) {
            maxHeight = childHeight;
        }
    }

    return 1 + maxHeight;
}

Node* search(Node* root, char value) {
    if(root == NULL) return NULL;

    if(root->data == value) return root;

    for(int i = 0; i < root->count; i++) {
        Node* found = search(root->next[i], value);
        if(found != NULL) return found;
    }

    return NULL;
}

int main() {
    Node* root = createNode('A');
    addNode(root, 3, 'B', 'C', 'D');
    addNode(root, 1, 'E');
    addNode(root->next[0], 2, 'F', 'G');
    show(root, 0);
    printf("Height: %d\n", height(root));
    return 0;
}