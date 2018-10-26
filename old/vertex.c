#include "vertex.h"

typedef struct vertex {
	char* name;
	double weight;
} vertex;

vertex* new_empty_vertex() {
	vertex* v = (vertex*) malloc(sizeof(vertex));
	v->name = '\0';
	v->weight = 0.0;
	return v;
}

vertex* new_vertex(char* s, double weight) {
	vertex* v = (vertex*) malloc(sizeof(vertex));
	strcpy(v->name, s);
	v->weight = weight;
	return v;
}
