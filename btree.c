#include <stdio.h>
#include "lib.h"

typedef struct btree btree;

boolean btree_insert(btree *self, void *value);
boolean btree_contains(btree *self, void *value);
//void btree_delete(btree *self, void *value);
boolean btree_is_leaf(btree *self);
void btree_clear(btree *self);

struct btree {
	void* value;
	TYPE type;
	struct btree* left;
	struct btree* right;
};

btree* new_btree(void* value, TYPE type) { // optional value; use NULL if not value
	btree *self = malloc(sizeof(btree));
    if (self == NULL) return NULL;
	self->value = value;
	self->type = type;
	self->left = NULL;
	self->right = NULL;
	return self;
}

boolean btree_insert(btree *self, void *value) {
	if (self == NULL) return BAD_REF;
	int cmp = compare(self->value, value, self->type);
	if (cmp == COMPARISON_ERROR) return cmp;
	
    if (self->left == NULL && cmp < 1) {
        self->left = new_btree(value, self->type);
    }
    if (self->right == NULL && cmp > 0) {
        self->right = new_btree(value, self->type);
    }
	return btree_insert((cmp < 1 ? self->left : self->right) ,value);
}

boolean btree_contains(btree *self, void *value) {
    if (self == NULL) return BAD_REF;
    int cmp = compare(self->value, value, self->type);
    if (cmp == COMPARISON_ERROR) return cmp;
    if (cmp == 0) return true;
    if (self->left == NULL && cmp < 1) return false;
    if (self->right == NULL && cmp > 0)  return false;
    return btree_contains(((cmp < 1) ?  self->left : self->right), value);
}
/* TODO Complete:
boolean btree_delete(btree *self, void *value) {
	if (self == NULL) return BAD_REF;
	btree* modified_tree = btree_delete_helper(self, value);
	return self = modified_tree;
}

btree* btree_delete_helper(btree *self, void *value) {
	if (self == NULL) return BAD_REF;
	int cmp = compare(self->value, value, self->type);
	if (cmp == COMPARISON_ERROR) return cmp;

}
*/

boolean btree_is_leaf(btree *self) {
    if (self == NULL) return BAD_REF;
    return (self->left == NULL && self->right == NULL);
}

void btree_clear(btree *self) {
    if (self == NULL) return;
    btree* left = self->left;
    btree* right = self->right;
    free(self); //preserve stack space
    if (left != NULL)
        btree_clear(left);
    if (right != NULL)
        btree_clear(right);
}