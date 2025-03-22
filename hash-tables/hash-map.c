#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_MAP_SIZE 10

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

Node *hashMap[HASH_MAP_SIZE] = {NULL};

unsigned int hashFunction(const char *key) {
    int sum = 0;

    for(int i = 0; i < key[i] != '\0'; i++) {
        sum += key[i];
    }

    return sum % HASH_MAP_SIZE;
}

int size() {
    int sum = 0;

    for(int i = 0; i < HASH_MAP_SIZE; i++) {
        Node* current = hashMap[i];

        while(current != NULL) {
            sum++;
            current = current->next;
        }
    }

    return sum;
}

bool search(const char *key) {
    int index = hashFunction(key);
    Node* current = hashMap[index];

    while(current != NULL) {
        if(strcmp(current->key, key) == 0) {
            return true;
        }

        current = current->next;
    }

    return false;
}

void add(const char *key, int value) {
    if(search(key)) {
        printf("%s already has been used\n", key);
        return;
    } 

    int index = hashFunction(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = hashMap[index];
    hashMap[index] = newNode;
}

void delete(const char *key) {
    if(size() == 0) {
        printf("Hash map has nothing inside\n");
        return;
    }

    int index = hashFunction(key);
    Node* current = hashMap[index];
    Node* prev = NULL;

    while(current != NULL) {
        if(strcmp(current->key, key) == 0) {
            if(prev == NULL) {
                hashMap[index] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->next);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("No key %s found\n", key);
}

void show() {
    for(int i = 0; i < HASH_MAP_SIZE; i++) {
        printf("%d: ", i);
        Node* current = hashMap[i];
        while(current != NULL) {
            printf("\"%s\": \"%d\" -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    add("123", 10);
    add("456", 20);
    add("789", 30);
    show();
    return 0;
}