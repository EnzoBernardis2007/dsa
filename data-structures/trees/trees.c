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
    if(root == NULL) return;

    va_list args;
    va_start(args, count);

    for(int i = 0; i < count; i++) {
        if(root->count >= MAX) {
            break;
        }

        root->next[root->count] = createNode((char)va_arg(args, int)); // Corrigido va_arg para char
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

void findParent(Node* root, char value, Node** parent, int* index) {
    if(root == NULL) return;

    for(int i = 0; i < root->count; i++) {
        if(root->next[i]->data == value) {
            *parent = root;
            *index = i;
            return;
        }
        findParent(root->next[i], value, parent, index);
    }
}

void removeSubtree(Node* node) {
    if(node == NULL) return;

    for(int i = 0; i < node->count; i++) {
        removeSubtree(node->next[i]);
    }

    free(node);
}

void removeNodeAndChild(Node* root, char value) {
    if(root == NULL) return;

    if(root->data == value) {
        printf("Não é possível remover a raiz.\n");
        return;
    }

    Node* parent = NULL;
    int index = -1;

    findParent(root, value, &parent, &index);

    if(parent != NULL && index != -1) {
        removeSubtree(parent->next[index]);

        for(int i = index; i < parent->count - 1; i++) {
            parent->next[i] = parent->next[i + 1];
        }

        parent->next[parent->count - 1] = NULL;
        parent->count--;
    }
}

int countLeafs(Node* root) {    
    if(root == NULL) return 0;
    if(root->count == 0) return 1;
    
    int total = 0;

    for(int i = 0; i < root->count; i++) {
        total += countLeafs(root->next[i]);
    }

    return total;
}

int nodesInLevel(Node* root, int level, int currentLevel) {
    if(root == NULL) return 0;

    if(currentLevel == level) return 1;

    int total = 0;

    for(int i = 0; i < root->count; i++) {
        total += nodesInLevel(root->next[i], level, currentLevel + 1);
    }

    return total;
}

bool isBinary(Node* root) {
    for(int i = 0; i < root->count; i++) {
        if(!(root->count != 2 && root->count != 0)) {
            isBinary(root->next[i]);
        } else {
            return false;
        }
    }

    return true;
}

void invertTree(Node* root) {
    if(root == NULL) return;

    for(int i = 0, j = root->count - 1; i < j; i++, j--) {
        Node* temp =root->next[i];
        root->next[i] = root->next[j];
        root->next[j] = temp;
    }

    for(int i = 0; i < root->count; i++) {
        invertTree(root->next[i]);
    }
}

int main() {
    Node* root = createNode('A');
    addNode(root, 3, 'B', 'C', 'D');
    addNode(root->next[1], 2, 'E', 'F');
    addNode(root->next[1], 4, 'G', 'H', 'I', 'J');
    show(root, 0);
    return 0;
}