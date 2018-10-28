#include <stdio.h>
#include "lib.h"

/********** A Lot of functionality is very similar to STACK so I might find a way to compact out the code base
*********************/

typedef struct array_list array_list;

/*function prototypes*/
boolean insert(array_list* self, void* value);
void* get(array_list* self, int position);
boolean set(array_list* self, void* value, int position);
int search(array_list* self, void* value);
//add more?
boolean delete(array_list* self, int position);
void** to_array(array_list* self);
void clear(array_list* self);

struct array_list {
    void** array;
    TYPE type;
    int capacity;
    int position;    

    boolean (*insert)(array_list* self, void* value);
    void* (*get)(array_list* self, int position);
    boolean (*set)(array_list* self, void* value, int position);
    int (*search)(array_list* self, void* value);
    //add more?
    boolean (*delete)(array_list* self, int position);
    void** (*to_array)(array_list* self);
    void (*clear)(array_list* self);
};

array_list* new_array_list(void* value, TYPE type, int capacity) {
    array_list *self = malloc(sizeof(array_list));
    if (self == NULL) return NULL;
    self->type = type;
    self->capacity = capacity;
    self->array = malloc(sizeof(void*)*capacity);
    if (self->array == NULL) return NULL;
    for (int i = 0; i < capacity; i++) {
        self->array[i] = malloc(sizeof(uint64_t)); //should I be careful here? Perhaps define a way to differentiate between holding 32/64 bits
        if (self->array[i] == NULL) return NULL;
    }
    self->position = 0;
    self->array[0] = value;
    
    self->insert = array_list_insert;
    self->get = array_list_get;
    self->set = array_list_set;
    self->search = array_list_search;
    self->delete= array_list_search;
    self->to_array = array_list_to_array;
    self->clear = array_list_clear;
    return self;
}

boolean array_list_insert(array_list* self, void* value) {
    if (self == NULL) return false;
    if (self->position >= self->capacity -1) {
        void** new_arr = realloc(self->array, self->capacity*2);
        if (new_arr == NULL) return ALLOC_ERROR;
        self->capacity *= 2;
        for (int i = self->capacity/2; i < self->capacity; i++) {
            new_arr[i] = malloc(sizeof(uint64_t));
            if (new_arr[i] == NULL) return ALLOC_ERROR;
        } 
    }
    self->position += 1;
    self->array[self->position] = value;
    return true;
}

void* array_list_get(array_list* self, int position) {
    if (self == NULL || position >= self->capacity) return NULL;
    return self->array[position];
}

boolean array_list_set(array_list* self, void* value, int position) {
    if (self == NULL || position >= self->capacity) return false;
    self->array[position] = value;
    return true;
}

int array_list_search(array_list* self, void* value) {
    if (self == NULL) return BAD_REF;
    for (int i = 0; i <= self->position; i++) {
        if (compare(self->array[i], value, self->type) == 0) return i;
    }
    return -1;
}
//add more?

boolean array_list_delete(array_list* self, int position) {
    if (self == NULL || position >= self->capacity) return BAD_REF;
    for (int i = position; i < self->position; i++) {
        self->arr[i] = self->arr[i+1];
    }
    self->position -= 1;
    return true;
}

void** array_list_to_array(array_list* self) {
    if (self == NULL) return NULL;
    return self->array;
}

void array_list_clear(array_list* self) {
    if (self == NULL) return;
    int (i = self->capacity-1; i >= 0; i--) {
        free(self->array[i]);
    }
    free(self->array);
}
