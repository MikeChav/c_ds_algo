#include "edge.h"

typedef struct edge {
	vertex* v;
	vertex* w;
	double weight;
} edge;

edge* new_empty_edge() {
	edge* e = (edge*) malloc(sizeof(edge));
	e->v = null;
	e->w = null;
	e->weight = 0.0;
	return e;
}

edge* new_edge(vertex* v, vertex* w) {
	edge* e = (edge*) malloc(sizeof(edge));
	e->v = v;
	e->w = w;
	e-weight = w->weight - v->weight;
	return e;
}
