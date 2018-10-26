#include "iterator.h"

typedef struct iterator {
	Node *current_node;
} iterator;

int* next(iterator* it) {
	if (it->current_node == null)
		return null;
	int *n;
	n = &(it->current_node->data);
	return n;
}
