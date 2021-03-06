#include <stdio.h>
#include "lib.h"

typedef struct list list;

list* new_list(void *value, TYPE type);
boolean list_insert(list* self, void* value);
boolean list_contains(list* self, void* value);
boolean list_delete(list* self, void* value);
//void list_sort(list* self);
void list_print(list* self);
void list_clear(list* self);

struct list {
	void *value;
	TYPE type;
	struct list *prev;
	struct list *next;
	boolean (*insert)(list *self, void *value);
	boolean (*contains)(list *self, void *value);
	boolean (*delete)(list *self, void *value);
	//void (*sort)(list *self);
	void (*print)(list *self);
    void (*clear)(list* self);
};

list *new_list(void *value, TYPE type) {
	list *ll = malloc(sizeof(list));
	if (ll == NULL) return NULL;
    ll->value = value;
	ll->type = type;
	ll->prev = NULL;
	ll->next = NULL;
	ll->insert = list_insert;
	ll->contains = list_contains;
	ll->delete = list_delete;
	//ll->sort = list_sort;
	ll->print = list_print;
    ll->clear = list_clear;
	return ll;
}

boolean list_insert(list *self, void *value) {
	if (self == NULL) return BAD_REF;
	list *curr = self;
    for (; curr->next != NULL; curr = curr->next);
	curr->next = new_list(value, self->type);
    curr->next->prev = curr;
	return true;
}

boolean list_contains(list *self, void *value) {
	if (self == NULL) return BAD_REF;
	for (list *curr = self; curr != NULL; curr = curr->next) {
		if (compare(self->value, value, self->type) == 0) return true;
	}
	return false;
}

boolean list_delete(list *self, void *value) {
    if (self == NULL) return BAD_REF;
    for (list *curr = self; curr != NULL; curr = curr->next) {
        if (compare(self->value, value, self->type) == 0) {
            list* to_delete = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            free(curr);
            return true;
        }
    }
    return false;
}
/*
void sort(list *self) {
    //merge sort?
    //bubble sort easier to implement
    //to_array possible -> maybe return a union that holds pointers to each datatype and have user extract/cast?
}
*/
/*
Arrays to_array(list *self) {
    int count = 0;
    for (list *curr = self; curr != NULL; curr = curr->next, count++);
    
    for (list *curr = self; curr != NULL; curr = curr->next) {

    }
}
*/

void list_print(list *self) {
    for (list* curr = self; curr != NULL; curr = curr->next) {
        char *s = to_string(curr->value, curr->type);
        printf("%s\n", s);
        free(s);
    }
}

void list_clear(list* self) {
    if (self->next == NULL) {
        free(self);
    }
    else {
        list* next = self->next;
        free(self);
        list_clear(next);
    }
}
