#include "lib.h"

extern struct btree_node

extern struct btree;

extern btree_node* new_btree_node(char *s);

extern btree* new_btree(char* s);

extern void insert_helper(btree_node* tree, char *s);

extern void insert(btree* tree, char *s);

extern boolean search_helper(btree_node* tree, char* s);

extern boolean search(btree *tree, char* s);

extern boolean delete_helper(btree_node* tree, char* s);

extern boolean delete(btree *tree, char* s);

extern void inorder_helper(btree_node *tree);

extern void print_inorder(btree *tree);

extern void preorder_helper(btree_node *tree);

extern void print_preorder(btree *tree);

extern void postorder_helper(btree_node *tree);

extern void print_postorder(btree *tree);
