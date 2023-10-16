#include <stdio.h>
#include <stdint.h>

#include "lib.h"

typedef struct stack stack;

void* stack_pop(stack* self);
void* stack_push(stack* self, void* val);
boolean stack_empty(stack* self);
void stack_clear(stack* self);

struct stack {
    void **array;
    TYPE type;
    int capacity;
    int top;
};

stack* new_stack(TYPE type, int capacity) {
    stack *self = malloc(sizeof(stack));
    if (self == NULL) return NULL;
    self->array = malloc(sizeof(void*)*capacity);
    if (self->array == NULL) return NULL;
    for (int i = 0; i < capacity; i++) {
        self->array[i] = malloc(sizeof(uint64_t));
        if (self->array[i] == NULL) return NULL;
    }
    self->type = type;
    self->capacity = (capacity == 0) ? 1 : capacity;
    self->top = -1;
    return self;
}

void* stack_pop(stack* self) { // pop on an empty stack is undefined behavior
    int top = self->top;
    self->top--;
    if (self->top >= 0) {
        return self->array[top];
    }
    return NULL; //NULL == (void *) 0 so user may think this is a value; should check if empty first
}

void* stack_push(stack* self, void* val) { // returns ref to inserted item
    if (self->top == (self->capacity-1)) {
        self->capacity *= 2;
        self->array = realloc(self->array, self->capacity*sizeof(void**));
        if (self->array == NULL) return false; 
        for (int i = self->capacity/2; i < self->capacity; i++) {
            self->array[i] = malloc(sizeof(uint64_t));
            if (self->array[i] == NULL) return NULL;
        }
    }
    self->array[++self->top] = val;
    return &(self->array[self->top]);
}

boolean stack_empty(stack* self) {
    return self->top < 0;
}

void stack_clear(stack* self) {
    for (int i = 0; i < self->capacity; i++) {
        free(self->array[i]);
    }
    free(self->array);
    free(self);
}

/*
Example usage

int main() {
    stack* s = new_stack(INT, 2);

    stack_push(s, 3);
    stack_push(s, 5);
    stack_push(s, 2); // realloc should occur here

    printf("%d\n", (*int)(stack_pop(s))); // expect 2
    if (stack_empty(s)) {
        printf("First check, stack is empty.\n"); // expect this message
    }
    else {
        printf("First check, stack is not empty.\n");
    }
    stack_clear(s);
    if (stack_empty(s)) {
        printf("Second check, stack is empty.\n"); // expect this message
    }
    else {
        printf("Second check, stack is not empty.\n");
    }

}


*/
