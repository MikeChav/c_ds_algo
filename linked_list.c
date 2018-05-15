#include "LinkedList.h"

typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct LinkedList {
	struct Node *head;
	struct Node *tail;
	int size;
} LinkedList;


Node* new_node(int n) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->data = 0;
	temp->prev = null;
	temp->next = null;
	return temp;
}

LinkedList *new_empty_linked_list() {
	LinkedList *temp = (LinkedList*) malloc(sizeof(LinkedList));
	temp->head = null;
	temp->tail = temp->head;
	temp->size = 0;
	return temp;
}

LinkedList *new_linked_list(int n) {
	LinkedList *temp = (LinkedList*) malloc(sizeof(LinkedList)); //could use new_empty_linked_list() but it's a useless function call
	temp->head = new_node(n);
	temp->tail = temp->head;
	temp->size = 1;
}

void insert(LinkedList* ll, int n) {
	if (ll->head == null) {
		ll->head = new_node(n);
	}
	else {
		Node *old_tail = ll->tail;
		Node *new_tail = new_node(n);
		old_tail->next = new_tail;
		new_tail->prev = old_tail;
		ll->tail = new_tail;
	}
	ll->size++;
}

boolean search(LinkedList* ll, int n) {
	for (Node *curr = ll->head; curr != null; curr = curr->next) {
		if (curr->data == n)
			return true;
	}
	return false;
}

boolean delete(LinkedList* ll, int n) {
	for (Node *curr = ll->head; curr->next != null; curr = curr->next) {
		if (curr->next->data == n) {
			Node *to_delete = curr->next;
			Node *prev = curr;
			Node *next = curr->next->next;
			prev->next = next;
			next->prev = prev;
			free(to_delete); //Is correct?
			return true;
		}
	}
	return false;
}

void sort(LinkedList* ll) { //Lord help me here
	if (ll->head == null || ll->head->next == null) {
		return;
	}

	LinkedList *half1 = new_empty_linked_list(), half2 = new_empty_linked_list();
	for (Node *p1 = ll->head, *p2 = ll->head->next; p2 != null; p1 = p2->next, p2 = p1->next) {
		insert(half1, p1->data);
		insert(half2, p2->data);
	}

	if (p1 != null && p2 == null) {
		insert(half1, p1->data);
	}

	sort(half1);
	sort(half2);
	
	ll->head = merge(half1->head, half2->head);
}

Node* merge(Node *half1, Node *half2) {
	Node *result = null;
	if (half1 == null) {
		return half2;
	}
	if (half2 == null) {
		return half1;
	}
	if (half1->data <= half2->data) {
		result = half1;
		Node* merged = merge(half1->next, half2);
		result->next = merged;
		merged->prev = result;
	}
	else {
		result = half2;
		Node *merged = merge(half1, half2->next);
		result->next = merged;
		merged->prev = result;
	}
	
	return result;
}

void print(LinkedList* ll) {
	for (Node *curr = ll->head; curr != null; curr = curr->next) {
		printf("%d ", curr->data);
	}
}
