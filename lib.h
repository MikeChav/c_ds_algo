#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define null (void*)0
#define true 1
#define false 0
#define boolean int
#define COMPARISON_ERROR 1000
#define BAD_REF 2000

typedef enum Type {
	INT,
	CHAR,
	STRING,
	FLOAT,
	DOUBLE,
	LONG,
	LONGLONG
} TYPE;

int compare(void* v1, void* v2, TYPE type) {
    int ia, ib;
    char ca, cb;
 //   char *sa, *sb;
    float fa, fb;
    double da, db;
    long la, lb;
    long long lla, llb;
    if (v1 == NULL || v2 == NULL)
        return COMPARISON_ERROR;
	switch(type) {
		case INT:
			ia = *((int*) v1);
			ib = *((int*) v2);
	        return ((ia < ib) ? -1 : ((ia == ib) ? 0 : 1)); 
		case CHAR:
			ca = *((char*) v1);
			cb = *((char*) v2);
	        return ((ca < cb) ? -1 : ((ca == cb) ? 0 : 1)); 
		case STRING:
/*
			sa = *((char**) v1);
			sb = *((char**) v2);
			return strcmp(sa, sb);
*/          return strcmp(*((char**) v1), *((char**) v2));
		case FLOAT:
			fa = *((float*) v1);
			fb = *((float*) v2);
	        return ((fa < fb) ? -1 : ((fa == fb) ? 0 : 1)); 
		case DOUBLE:
			da = *((double*) v1);
			db = *((double*) v2);
	        return ((da < db) ? -1 : ((da == db) ? 0 : 1)); 
		case LONG:
			la = *((long*) v1);
		    lb = *((long*) v2);
	        return ((la < lb) ? -1 : ((la == lb) ? 0 : 1)); 
		case LONGLONG:
			lla = *((long long*) v1);
			llb = *((long long*) v2);
	        return ((lla < llb) ? -1 : ((lla == llb) ? 0 : 1)); 
	}
    return COMPARISON_ERROR;
}
