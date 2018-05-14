#include "tree.h"

typedef struct Tree {
	char[255] data;
	struct Tree* left;
	struct Tree* right;
} Tree;

Tree* new_node(char* s) {
	Tree * node = (Tree*) malloc(sizeof(Tree));
	strcpy(node->data, s);
	node->left = null;
	node->right = null;
	return node;
}

Tree* insert(Tree* tree, char *s) { //can be simplified
	if (tree == null)
		return null; //should never execute
	int res = strcmp(tree->data, s);
	if (res == 0)
		return tree;
	if (res < 0) {
		if (tree->left == null) {
			tree->left = new_node(s);
		}
		else {
			insert(tree->left, s);
		}
	}
	else {
		if (tree->right == null) {
			tree->right = new_node(s);
		}
		else {
			insert(tree->right, s);
		}
	}
	return tree;
}

boolean search(Tree *tree, char* s) {
	if (tree == null) return false;
	int res = strcmp(tree->data, s);
	if (res == 0) return true;
	if (res < 0) return search(tree->left, s);
	if (res > 0) return search(tree->right, s);
	return false;
}

void print_inorder(Tree *tree) {
	if (tree == null)
		return;
	print_inorder(tree->left);
	printf("%s ", s);
	print_inorder(tree->right);
}

void print_preorder(Tree *tree) {
	if (tree == null)
		return;
	printf("%s ", s);
	print_preorder(tree->left);
	print_preorder(tree->right);
}

void print_postorder(Tree *tree) {
	if (tree == null)
		return;
	print_postorder(tree->left);
	print_postorder(tree->right);
	printf("%s ", s);
}

boolean delete(Tree *tree, char* s, boolean search_first) { //test extensively
	if (search_first && !search(tree, s)) {
		return false;	
	}
	if (tree == null)
		return false;
	int res = strcmp(tree->data, s);
	if (res == 0) {
		if (tree->left == null && tree->right == null)
			free(tree);
		if (tree->left == null && tree->right != null) {
			tree = tree->right;
		}
		else if (tree->left != null && tree->right == null) {
			tree = tree->left;
		}
		else {
			Tree *temp = tree->left;
			tree = tree->right;
			tree->left = temp;
		}
		return true;
	}
	if (res < 0) return delete(tree->left, s);
	if (res > 0) return delete(tree->right, s);
	return false
}
