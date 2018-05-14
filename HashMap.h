#include "lib.h"

extern struct hash_map_node;

extern struct hash_map;

extern hash_map_node * new_hash_map_node();

extern hash_map* new_hash_map();

extern void insert(hash_map* map, int n);

extern boolean delete(hash_map* map, int n);

extern boolean search(hash_map* map, int n);

extern iterator* get_iterator(hash_map* map);


