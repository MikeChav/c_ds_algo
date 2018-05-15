#include "lib.h"

typedef btree hash_table_node;

extern struct hash_table;

extern hash_table_node* new_hash_table_node();

extern hash_table* new_hash_table();

extern void insert(hash_table* map, int n);

extern boolean delete(hash_table* map, int n);

extern boolean search(hash_table* map, int n);

extern iterator* get_iterator(hash_table* map);

extern void get_iterator_helper(iterator* it, hash_table_node *node);

extern int default_hash_function(hash_table* map, int value);
