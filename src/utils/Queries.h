/*
	This file and it's associated c file implement the different tree query functions
	to be created.
*/

#ifndef QUERIES_H
#define QUERIES_H

#include "Utils.h"

#define NUM_NEIGHBORS 10

void testCallBack (Node *curNd, unsigned int depth, void *params);

typedef struct
{
	unsigned int 	searchRadius;
	Node 		*rootNode;
	FILE		*outputFile;
} kNNParams;

typedef struct
{
	DataPointEntry 	*opDPE;
	unsigned int	neighborCount;
	double 		dists[NUM_NEIGHBORS];
	DataPointEntry 	*neighbors[NUM_NEIGHBORS];
} kNNWorkspace;

void initializekNNWorkspace (kNNWorkspace *workspace);
void printkNNWorkspace (FILE *outFile, kNNWorkspace *workspace);
void kNNCallBack (Node *curNd, unsigned int depth, void *params);
void updatekNNWorkspaceCallBack (Node *curNd, unsigned int depth, void *params);

void nodeCanAddrCheckCB (Node *curNd, unsigned int depth, void *params);
#endif
