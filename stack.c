#include <stdio.h>
#include "lib.h"

typedef struct stack {
    void **array;
    TYPE type;
    int capacity;
    int top;
    void* (*pop)(stack* self);
    void (*push)(stack* self, void* val);
    boolean (*is_empty)(stack* self);
//    void (*clear)(stack* self);
} stack;

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
        void** new_arr = (void**) malloc(sizeof(void*)*self->capacity);
        memcpy(new_arr, self->array, sizeof(self->arr)); //efficient? or move elements to array to avoid holding data twice <- memory vs time
        free(self->array);
        self->array = new_arr;
    }
    self->top = self->top +1;
    self->array[self->top] = val;
}

boolean stack_is_empty(stack* self) {
    return self->top < 0;
}

/** Might be useless
void clear(stack* self) {

}
*/
