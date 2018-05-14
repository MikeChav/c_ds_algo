#include "lib.h"

extern struct Tree;

extern Tree* new_node(char* s);

extern Tree* insert(Tree* tree, char *s);

extern boolean search(Tree *tree, char* s);

extern void print_inorder(Tree *tree);

extern void print_preorder(Tree *tree);

extern void print_postorder(Tree *tree);

extern boolean delete(Tree *tree, char* s, boolean search_first);
