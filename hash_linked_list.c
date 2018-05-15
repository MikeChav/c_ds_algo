#include "linked_list.h"

typedef struct hash_linked_list {
	hash_linked_list_node* buckets;
	int size;
	int (*hash_function)(struct hash_linked_list*, void*);
//	int (*comparator)(void*, void*);
} hash_linked_list;

hash_linked_list_node* new_hash_linked_list_node() {
	return new_empty_linked_list();
}

hash_linked_list* new_hash_linked_list(hash_linked_list* hll, int size) {
	hash_linked_list* hll = (hash_linked_list*) malloc(sizeof(hash_linked_list));
	hll->size = size;
	hll->buckets = (hash_linked_list_node*) malloc(size*sizeof(hash_linked_list_node));
	hll->hash_function = &default_hash_function;
	return hll;
}

void insert(hash_linked_list* hll, int n) {
	insert(hll[hll->default_hash_function(hll, n)], n);
}

boolean delete(hash_linked_list* hll, int n) {
	return delete(hll[hll->default_hash_function(hll, n)], n);
}

boolean search(hash_linked_list* hll, int n) {
	return search(hll[hll->default_hash_function(hll, n)], n);
}

iterator* get_iterator(hash_linked_list* hll) {
	linked_list* ll = new_empty_linked_list();
	for (int i = 0; i < hll->size; i++) {
		get_iterator_helper(ll, hll[i]);
	}
	return ll->head;
}

void get_iterator_helper(linked_list* ll, hash_linked_list_node *list) {
	for (linked_list_node* curr = list->head; curr != null; curr = curr->next) {
		insert(ll, curr->data);
	}
}

int default_hash_function(hash_linked_list* hll, int value) {
	return value % hll->size;
}


