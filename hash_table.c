#include "btree.h"
#include "linked_list.h"

typedef struct hash_table {
	hash_table_node* buckets;
	int size;
	int (*hash_function)(struct hash_table*, void*);
//	int (*comparator)(void*, void*);
} hash_table;

hash_table_node* new_hash_table_node() {
	return new_empty_btree();
}

hash_table* new_hash_table(hash_table* map, int size) {
	hash_table* map = (hash_table*) malloc(sizeof(hash_table));
	map->size = size;
	map->buckets = (hash_table_node*) malloc(size*sizeof(hash_table_node));
	map->hash_function = &default_hash_function;
	return map;
}

void insert(hash_table* map, int n) {
	insert(map[map->default_hash_function(map, n)], n);
}

boolean delete(hash_table* map, int n) {
	return delete(map[map->default_hash_function(map, n)], n);
}

boolean search(hash_table* map, int n) {
	return search(map[map->default_hash_function(map, n)], n);
}

iterator* get_iterator(hash_table* map) {
	linked_list* ll = new_empty_linked_list();
	for (int i = 0; i < map->size; i++) {
		get_iterator_helper(ll, map[i]->root);
	}
	return ll->head;
}

void get_iterator_helper(linked_list* ll, btree_node *node) {
	if (node == null) {
		return;
	}
	get_iterator_helper(ll, node->left);
	insert(ll, node->data);
	get_iterator_helper(ll, node->right);
} 

int default_hash_function(hash_table* map, int value) {
	return value % map->size;
}


