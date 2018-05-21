#include "linked_hash_map.h"

typedef struct linked_hash_map {
	linked_hash_map_node* buckets;
	int size;
	int (*hash_function)(struct linked_hash_map*, void*);
//	int (*comparator)(void*, void*);
} linked_hash_map;

linked_hash_map_node* new_linked_hash_map_node() {
	return new_empty_linked_list();
}

linked_hash_map* new_linked_hash_map(linked_hash_map* hll, int size) {
	linked_hash_map* hll = (linked_hash_map*) malloc(sizeof(linked_hash_map));
	hll->size = size;
	hll->buckets = (linked_hash_map_node*) malloc(size*sizeof(linked_hash_map_node));
	hll->hash_function = &default_hash_function;
	return hll;
}

void insert(linked_hash_map* hll, int n) {
	insert(hll[hll->default_hash_function(hll, n)], n);
}

boolean delete(linked_hash_map* hll, int n) {
	return delete(hll[hll->default_hash_function(hll, n)], n);
}

boolean search(linked_hash_map* hll, int n) {
	return search(hll[hll->default_hash_function(hll, n)], n);
}

iterator* get_iterator(linked_hash_map* hll) {
	linked_list* ll = new_empty_linked_list();
	for (int i = 0; i < hll->size; i++) {
		get_iterator_helper(ll, hll[i]);
	}
	return ll->head;
}

void get_iterator_helper(linked_list* ll, linked_hash_map_node *list) {
	for (linked_list_node* curr = list->head; curr != null; curr = curr->next) {
		insert(ll, curr->data);
	}
}

int default_hash_function(linked_hash_map* hll, int value) {
	return value % hll->size;
}


