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

hash_table* new_hash_table(hash_table* table, int size) {
	hash_table* table = (hash_table*) malloc(sizeof(hash_table));
	table->size = size;
	table->buckets = (hash_table_node*) malloc(size*sizeof(hash_table_node));
	table->hash_function = &default_hash_function;
	return table;
}

void insert(hash_table* table, int n) {
	insert(table[table->default_hash_function(table, n)], n);
}

boolean delete(hash_table* table, int n) {
	return delete(table[table->default_hash_function(table, n)], n);
}

boolean search(hash_table* table, int n) {
	return search(table[table->default_hash_function(table, n)], n);
}

iterator* get_iterator(hash_table* table) {
	linked_list* ll = new_empty_linked_list();
	for (int i = 0; i < table->size; i++) {
		get_iterator_helper(ll, table[i]->root);
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

int default_hash_function(hash_table* table, int value) {
	return value % table->size;
}


