#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    if(new_node == NULL) return NULL;

    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// left = 0, right = 1
void insert_node(Node* root, int value, int direction) {
    Node* new_node = create_node(value);

    switch (direction) {
    case 0:
        if(root->left != NULL) {
            free(root->left);
        }
        root->left = new_node;
        break;
    case 1:
        if(root->right != NULL) {
            free(root->right);
        }
        root->right = new_node;
        break;
    }
}

Node* search_node(Node* root, int value) {
    if(root == NULL) return NULL;
    
    if(root->data == value) return root;

    Node* left = search_node(root->left, value);
    if(left != NULL) return left;

    Node* right = search_node(root->right, value);
    if(right != NULL) return right;

    return NULL;
}

void remove_subtree(Node* root) {
    if(root == NULL) return;

    remove_subtree(root->left);
    remove_subtree(root->right);

    free(root);
}

int size(Node* root) {
    if(root == NULL) return 0;

    int total = 1;

    total += size(root->left) + size(root->right);

    return total;
}

int height(Node* root) {
    if(root == NULL) return -1;

    int max_height = 0;

    int left_child_height = height(root->left);
    if(left_child_height > max_height) {
        max_height = left_child_height;
    }

    int right_child_height = height(root->right);
    if(right_child_height > max_height) {
        max_height = right_child_height;
    }

    return 1 + max_height;
}

void show_tree(Node* root, int level) {
    if(root == NULL) return;

    for(int i = 0; i < level; i++) {
        printf("   ");
    }
    
    printf("%d\n", root->data);

    show_tree(root->left, level + 1);
    show_tree(root->right, level + 1);
}

int main() {
    Node* root = create_node(10);
    insert_node(root, 20, 0);
    insert_node(root, 30, 1);
    insert_node(root->left, 40, 0);
    insert_node(root->left, 50, 1);
    insert_node(root->right, 60, 0);
    insert_node(root->right, 70, 1);
    show_tree(root, 0);

    printf("%d\n", height(root));
}