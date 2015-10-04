/*
	This file and it's associated c file implement the different tree query functions
	to be created.
*/

#ifndef QUERIES_H
#define QUERIES_H

#include "Utils.h"

void testCallBack (Node *curNd, unsigned int depth, void *params);

typedef struct
{
	unsigned int maxSearchNum;
	unsigned int searchDist;
	Node *rootNode;
} kNNParams;
void kNNCallBack (Node *curNd, unsigned int depth, void *params);

#endif
