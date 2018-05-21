#include "lib.h"

typedef linked_list linked_hash_map_node;

extern struct linked_hash_map;

extern linked_hash_map_node* new_hash_table_node();

extern linked_hash_map* new_hash_table();

extern void insert(linked_hash_map* hll, int n);

extern boolean delete(linked_hash_map* hll, int n);

extern boolean search(linked_hash_map* hll, int n);

extern iterator* get_iterator(linked_hash_map* hll);

extern void get_iterator_helper(iterator* it, linked_hash_map_node *node);

extern int default_hash_function(linked_hash_map* hll, int value);
