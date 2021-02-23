#include <stdio.h>
#include "lib.h"

typedef struct btree btree;

boolean btree_insert(btree *self, void *value);
boolean btree_contains(btree *self, void *value);
//void btree_delete(btree *self, void *value);
boolean btree_is_leaf(btree *self);
void* btree_get_value(btree *self);
void btree_clear(btree *self);

struct btree {
	void* value;
	TYPE type;
	struct btree* left;
	struct btree* right;
	boolean (*insert)(btree* self, void* value);
	boolean (*contains)(btree* self, void* value);
//	void (*delete)(btree* self, void* value);
	boolean (*is_leaf)(btree* self);
	void* (*get_value)(btree* self);
    void (*clear)(btree* self);
	//todo continue adding definitions
};

btree* new_btree(void* value, TYPE type) {
	btree *self = malloc(sizeof(btree));
    if (self == NULL) return NULL;
	self->value = value;
	self->type = type;
	self->left = NULL;
	self->right = NULL;
	self->insert = btree_insert;
	self->contains = btree_contains;
//	self->delete = btree_delete;
	self->is_leaf = btree_is_leaf;
	self->get_value = btree_get_value;
    self->clear = btree_clear;
	return self;
}

boolean btree_insert(btree *self, void *value) {
	if (self == NULL) return BAD_REF;
	int cmp = compare(self->value, value, self->type);
	if (cmp == COMPARISON_ERROR) return cmp;
	
    if (self->left == NULL && cmp < 1) {
        self->left = new_btree(value, self->type);
        return true;
    }
    if (self->right == NULL && cmp > 0) {
        self->right = new_btree(value, self->type);
        return true;
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

void* btree_get_value(btree *self) {
    if (self == NULL) return NULL;
    return self->value;
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

/*
 *Idea: use a struct variant/union to hold all instances of a shared function.
 	Then have all the structs hold instances of this struct
  Idea 2: use a macro/preprocessor command to define some weird ass type, and have it be defined when the DS is declared in the constructor!!!!!
  To combat issue of several functions having same name, define them using macros, and perhaps `unset` them? Would that preserve the function?
	
  Idea 3: Keep a wrapper struct that keeps track of head/root and current, and function pointers, so that we don't have to do it in all structs.
  	  Keeping track of current also allows to not have `self` anymore (perhaps?)
 * */
