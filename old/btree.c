#include "btree.h"

typedef struct btree_node {
	char[255] data;
	struct btree* left;
	struct btree* right;
} btree_node;

typedef struct btree {
	btree_node* root;
	int size;
} btree;

btree_node* new_btree_node(char* s) {
	btree_node * node = (btree_node*) malloc(sizeof(btree_node));
	strcpy(node->data, s);
	node->left = null;
	node->right = null;
	return node;
}

btree* new_empty_btree() {
	btree* tree = (btree*) malloc(sizeof(btree));
	tree->root = null;
	tree->size = 0;
	return tree;
}

btree* new_btree(char *s) {
	btree* tree = (btree*) malloc(sizeof(btree));
	tree->root = new_btree_node(s);
	tree->size = 1;
	return tree;
}

void insert_helper(btree_node* tree, char *s) { //can be simplified
	int res = strcmp(tree->data, s);
	if (res == 0)
		return;
	if (res < 0) {
		if (tree->left == null) {
			tree->left = new_node(s);
		}
		else {
			insert_helper(tree->left, s);
		}
	}
	else {
		if (tree->right == null) {
			tree->right = new_node(s);
		}
		else {
			insert_helper(tree->right, s);
		}
	}
}

void insert(btree* tree, char *s) {
	insert_helper(tree->root, s);
}

boolean search_helper(btree_node *tree, char* s) {
	if (tree == null) return false;
	int res = strcmp(tree->data, s);
	if (res == 0) return true;
	if (res < 0) return search_helper(tree->left, s);
	if (res > 0) return search_helper(tree->right, s);
	return false;
}

boolean search(btree* tree, char*s) {
	return search_helper(tree->root, s);
}

void inorder_helper(btree_node *tree) {
	if (tree == null)
		return;
	inorder_helper(tree->left);
	printf("%s ", s);
	inorder_helper(tree->right);
}

void print_inorder(btree* tree, char* s) {
	inorder_helper(tree->root);
}

void preorder_helper(btree_node *tree) {
	if (tree == null)
		return;
	printf("%s ", s);
	preorder_helper(tree->left);
	preorder_helper(tree->right);
}

void print_preorder(btree* tree) {
	preorder_helper(tree->root);
}


void postorder_helper(btree_node *tree) {
	if (tree == null)
		return;
	postorder_node(tree->left);
	postorder_node(tree->right);
	printf("%s ", s);
}

void print_postorder(btree* tree) {
	postorder_helper(tree->root);
}

boolean delete_helper(btree_node *tree, char* s) { //test extensively
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
			btree *temp = tree->left;
			tree = tree->right;
			tree->left = temp;
		}
		return true;
	}
	if (res < 0) return delete_helper(tree->left, s);
	if (res > 0) return delete_helper(tree->right, s);
	return false
}

boolean delete(btree_node *tree, char *s) {
	if (delete_helper(tree->root, s)) {
		tree->size--;
		return true;
	}
	return false;
}
