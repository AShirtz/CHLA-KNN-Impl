/*
	This file and its associated header file implement the different tree queries.
*/

#include "Queries.h"

void testCallBack (Node *curNd, unsigned int depth, void *params)
{
	printDataPointEntry((FILE *)params, curNd->parkedDPE);
	fprintf((FILE *)params, "\n\n");
}

void kNNCallBack (Node *curNd, unsigned int depth, void *params)
{
	LatAddr extrema[8];
	// TODO: I'm heading to bed, this is where I left off
}
