#include "lib.h"

extern struct Node;

extern struct LinkedList; //doubly

extern Node* new_node(int n);

extern LinkedList *new_empty_linked_list();

extern LinkedList *new_linked_list(int n);

extern void insert(LinkedList* ll, int n);

extern boolean search(LinkedList* ll, int n);

extern boolean delete(LinkedList* ll, int n);

extern Node *merge(Node *half1, Node *half2);

extern void sort(LinkedList *ll);

extern void print(LinkedList* ll);
