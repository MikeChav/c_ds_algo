#include "lib.h"

typedef linked_list hash_linked_list_node;

extern struct hash_linked_list;

extern hash_linked_list_node* new_hash_table_node();

extern hash_linked_list* new_hash_table();

extern void insert(hash_linked_list* hll, int n);

extern boolean delete(hash_linked_list* hll, int n);

extern boolean search(hash_linked_list* hll, int n);

extern iterator* get_iterator(hash_linked_list* hll);

extern void get_iterator_helper(iterator* it, hash_linked_list_node *node);

extern int default_hash_function(hash_linked_list* hll, int value);
