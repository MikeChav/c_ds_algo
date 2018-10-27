#include <stdio.h>
#include "lib.h"
typedef struct stack stack;

void* stack_pop(stack* self);
void stack_push(stack* self, void* val);
boolean stack_is_empty(stack* self);
void stack_clear(stack* self);

struct stack {
    void **array;
    TYPE type;
    int capacity;
    int top;
    void* (*pop)(stack* self);
    void (*push)(stack* self, void* val);
    boolean (*is_empty)(stack* self);
    void (*clear)(stack* self);
};

stack* new_stack(void *val, TYPE type, int capacity) {
    stack *self = malloc(sizeof(stack));
    self->array = malloc(sizeof(void*)*capacity);
    for (int i = 0; i < capacity; i++) {
        self->array[i] = malloc(sizeof(char));
    } 
    self->array[0] = val;
    self->type = type;
    self->capacity = capacity;
    self->top = 0;
    self->pop = stack_pop;
    self->push = stack_push;
    self->is_empty = stack_is_empty;
    self->clear = stack_clear;
    return self;
}

void* stack_pop(stack* self) {
    int top = self->top;
    if (self->top >= 0) {
        self->top = top-1;
        return self->array[top];
    }
    return NULL; //potential error that stack stores int and user believes zero is being returned. User should check if empty
}

void stack_push(stack* self, void* val) {
    if (self->top >= (self->capacity-1)) {
        self->capacity = self->capacity*2;
        void **new_arr = realloc(self->array, self->capacity*sizeof(void**));
        for (int i = self->capacity/2; i < self->capacity; i++) {
            new_arr[i] = malloc(sizeof(char));
        }
        self->array = new_arr;
    }
    self->top = self->top +1;
    self->array[self->top] = val;
}

boolean stack_is_empty(stack* self) {
    return self->top < 0;
}

void stack_clear(stack* self) {
    for (int i = 0; i < self->capacity; i++) {
        free(self->array[i]);
    }
    free(self->array);
    free(self);
}
