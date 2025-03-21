#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

void initialize(Stack *s) {
    s->top = -1;
}

void push(Stack *s, int count, ...) {
    va_list args;
    va_start(args, count);

    for(int i = 0; i < count; i++) {
        if(s->top == MAX - 1) {
            printf("Stack overflow\n");
            va_end(args);
            return;
        }
        s->items[++(s->top)] = va_arg(args, int);
    }

    va_end(args);
}

void pop(Stack *s, int count) {
    if(isEmpty(s)) {
        return;
    }

    if(s->top - count < 0) {
        s->top = -1;
    } else {
        s->top -= count;
    }
}

void show(Stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("%d: %d\n", i, s->items[i]);
    }
}

int peek(Stack *s) {
    return s->items[s->top];
}

int size(Stack *s) {
    return s->top + 1;
}

void copyTopValue(Stack *s) {
    s->top++;
    s->items[s->top] = s->items[s->top - 1];
}

void swapTop(Stack *s) {
    int temp = s->items[s->top - 1];
    s->items[s->top - 1] = s->items[s->top];
    s->items[s->top] = temp;
}

void revert(Stack *s) {
    Stack aux;
    initialize(&aux);

    while(size(s) > 0) {
        push(&aux, 1, peek(s));
        pop(s, 1);
    }

    *s = aux;
}

int main() {
    Stack stack;
    initialize(&stack);
    push(&stack, 3, 1, 2, 3);
    revert(&stack);
    show(&stack);

    return 0;
}