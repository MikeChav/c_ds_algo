#include <stdio.h>
#include "lib.h"

typedef struct list {
	void *value;
	TYPE type;
	struct list *prev;
	struct list *next;
	boolean (*insert)(list *self, void *value);
	boolean (*contains)(list *self, void *value);
	boolean (*delete)(list *self, void *value);
	void (*sort)(list *self);
	void (*print)(list *self);
	char* (*to_string)(list *self);
} list;

list *new_list(void *value, TYPE, type) {
	list *ll = (list*) malloc(sizeof(list));
	ll->value = value;
	ll->type = type;
	ll->prev = NULL;
	ll->next = NULL;
	ll->insert = list_insert;
	ll->contains = list_contains;
	ll->delete = list_delete;
	ll->sort = list_sort;
	ll->print = list_print;
	ll->to_string = list_to_string;
	return ll;
}

boolean list_insert(list *self, void *value) {
	if (self == NULL) return BAD_REF;
	for (list *curr = self; curr->next != NULL; curr = curr->next);
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

void print(list *self) {
    for (list *curr; curr != NULL; curr = curr->next) {
        printf("%s\n", curr->to_string(curr));
    }
}

char* to_string(list *self) {
    char s[256];
	switch(self->type) {
		case INT:
			int *a = (int*) self->value;
            sprintf(s, "%d", *a);
		    break;
		case CHAR:
			char *a = (char*) self->value;
            sprintf(s, "%c", *a);
			break;
		case STRING:
			char **a = (char**) self->value;
            sprintf(s, "%s", *a);
			break;
		case FLOAT:
			float *a = (float*) self->value;
            sprintf(s, "%f", *a);
			break;
		case DOUBLE:
			double *a = (double*) self->value;
			sprintf(s, "%f", *a);
			break;
		case LONG:
			long *a = (long*) self->value;
			sprintf(s, "%ld", *a); 
			break;
		case LONGLONG:
			long long *a = (long long*) self->value;
			sprintf(s, "%lld", *a);
			break;
		default: return NULL;
	}
    return s;
}
