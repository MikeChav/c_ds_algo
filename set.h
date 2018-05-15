#include "btree.h"

typedef btree set;

void set_insert(set* Set, char* s) {
	if (!search(Set->root, s) {
		insert(Set, s);		
	}
}
