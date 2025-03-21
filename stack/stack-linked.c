#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top + 1 == s->capacity;
}

int size(Stack *s) {
    return s->top + 1;
}

Stack* createStack(int initialCapacity) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));

    if(newStack == NULL) {
        printf("Error trying allocate memory\n");
        exit(1);
    }

    newStack->data = (int*)malloc(initialCapacity * sizeof(int));
    newStack->top = -1;
    newStack->capacity = initialCapacity;

    return newStack;
}

void push(Stack *s, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        s->data[++(s->top)] = va_arg(args, int);
    }

    va_end(args);
}

void pop(Stack *s, int count) {
    if(count > size(s)) {
        s->top = -1;
    } else {
        s->top -= count;
    }
}

void show(Stack *s) {
    for(int i = s->top; i >= 0; i--) {
        printf("%d: %d\n", i, s->data[i]);
    }
}

int peek(Stack *s) {
    return s->data[s->top];
}

void copyTopValue(Stack *s) {
    s->data[s->top + 1] = s->data[s->top];
    s->top++;
}

void swapTop(Stack *s) {
    int temp = s->data[s->top - 1];
    s->data[s->top - 1] = s->data[s->top];
    s->data[s->top] = temp;
}

void revert(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Cannot revert.\n");
        return;
    }

    int *temp = (int*)malloc(s->capacity * sizeof(int));
    if (temp == NULL) {
        printf("Error: Failed to allocate memory for reverting stack.\n");
        exit(1);
    }

    int index = 0;

    while (!isEmpty(s)) {
        temp[index++] = peek(s);
        pop(s, 1);
    }

    for (int i = 0; i < index; i++) {
        push(s, 1, temp[i]);
    }

    free(temp);
}


int main() {
    Stack* stack = createStack(10);
    push(stack, 3, 10, 20, 30);
    revert(stack);
    show(stack);

    return 0;
}