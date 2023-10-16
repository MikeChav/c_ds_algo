#include <stdio.h>
#include "lib.h"

// switched from original "list" name to avoid confusion with Python's list
typedef struct linkedlist linkedlist;

linkedlist* new_linkedlist(void *value, TYPE type);
linkedlist* linkedlist_insert(linkedlist* self, void* value);
boolean linkedlist_contains(linkedlist* self, void* value);
boolean linkedlist_delete(linkedlist* self, void* value);
void** linkedlist_to_array(linkedlist* self);
void linkedlist_print(linkedlist* self);
void linkedlist_clear(linkedlist* self);

struct linkedlist {
	void *value;
	TYPE type;
	struct linkedlist *prev;
	struct linkedlist *next;
};

linkedlist *new_linkedlist(void *value, TYPE type) { // provide a dummy value if don't wish to have a value
	linkedlist *ll = malloc(sizeof(linkedlist));
	if (ll == NULL) return NULL;
    ll->value = value;
	ll->type = type;
	ll->prev = NULL;
	ll->next = NULL;
	return ll;
}

linkedlist* linkedlist_insert(linkedlist *self, void *value) { // return ref to insertion point
	if (self == NULL) return NULL;
	linkedlist *curr = self;
    for (; curr->next != NULL; curr = curr->next);
	curr->next = new_linkedlist(value, self->type);
    curr->next->prev = curr;
	return curr->next;
}

boolean linkedlist_contains(linkedlist *self, void *value) {
	if (self == NULL) return BAD_REF;
	for (linkedlist *curr = self; curr != NULL; curr = curr->next) {
		if (compare(self->value, value, self->type) == 0) return true;
	}
	return false;
}

boolean linkedlist_delete(linkedlist *self, void *value) { // deletes the first occurrence of value
    if (self == NULL) return BAD_REF;
    for (linkedlist *curr = self; curr != NULL; curr = curr->next) {
        if (compare(self->value, value, self->type) == 0) {
            linkedlist* to_delete = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            free(curr);
            return true;
        }
    }
    return false;
}

void** linkedlist_to_array(linkedlist *self) {
    int count = 0;
    for (linkedlist *curr = self; curr != NULL; curr = curr->next, count++);
    
    void** arr = new_stack(self->type, count); // bit of a cheat, but it saves on code
    
    for (linkedlist *curr = self; curr != NULL; curr = curr->next) {
        stack_insert(arr, curr->value);
    }
    return arr;
}

void linkedlist_print(linkedlist *self) {
    for (linkedlist* curr = self; curr != NULL; curr = curr->next) {
        char *s = to_string(curr->value, curr->type);
        printf("%s\n", s);
        free(s);
    }
}

void linkedlist_clear(linkedlist* self) {
    linkedlist* curr = self;
    while (curr != NULL) {
        linkedlist* saved = curr->next;
        free(curr);
        curr = saved;
    }
}
