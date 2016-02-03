/*
	This file and its associated header file implement the different tree queries.
*/

#include "Queries.h"

void testCallBack (Node *curNd, unsigned int depth, void *params)
{
	printDataPointEntry((FILE *)params, curNd->parkedDPE);
	fprintf((FILE *)params, "\n\n");
}

void initializekNNWorkspace (kNNWorkspace *workspace)
{
	int i;
	for (i = 0; i < NUM_NEIGHBORS; i++)
	{
		workspace->neighbors[i] = NULL;
	}
	workspace->opDPE = NULL;
	workspace->neighborCount = 0;
}

void printkNNWorkspace (FILE *outFile, kNNWorkspace *workspace)
{
	fprintf(outFile, "%u, %g, %g, %g, ", 
		workspace->opDPE->id, 
		workspace->opDPE->vecAddr.x, 
		workspace->opDPE->vecAddr.y, 
		workspace->opDPE->vecAddr.z);

	unsigned int i;
	for (i  = 0; i < workspace->neighborCount; i++)
	{
		fprintf(outFile, "%u, %g, %g, %g, ", 
			workspace->neighbors[i]->id, 
			workspace->neighbors[i]->vecAddr.x, 
			workspace->neighbors[i]->vecAddr.y, 
			workspace->neighbors[i]->vecAddr.z);
		fprintf(outFile, "%g, ", workspace->dists[i]);
	}
	fprintf(outFile, "\n");
}

void kNNCallBack (Node *curNd, unsigned int depth, void *params)
{
	kNNWorkspace workspace;
	initializekNNWorkspace (&workspace);
	workspace.opDPE = curNd->parkedDPE;

	unsigned int radiusScale = 1;

	while (workspace.neighborCount < NUM_NEIGHBORS)
	{
		selectiveFlood	(((kNNParams *)params)->rootNode, 0,
				&(curNd->parkedDPE->lAddr),
				((kNNParams *)params)->searchRadius,
				updatekNNWorkspaceCallBack,
				&workspace);
	}

	printkNNWorkspace(((kNNParams *)params)->outputFile, &workspace);
}

void updatekNNWorkspaceCallBack (Node *curNd, unsigned int depth, void *params)
{
	kNNWorkspace *workspace = (kNNWorkspace *) params;
	DataPointEntry *candidateNeighbor = curNd->parkedDPE;

	if (candidateNeighbor->id == workspace->opDPE->id)
	{
		// DPE.id is used for equivalence
		// One cannot be their own neighbor
		return;
	}

	unsigned int i, j;

	for (i = 0; i < workspace->neighborCount; i++)
	{
		if (workspace->neighbors[i]->id == candidateNeighbor->id)
		{
			// We've already seen this point as a neighbor
			return;
		}
	}

	double dist;

	EucVec cpy = workspace->opDPE->vecAddr;
	scaleEucVec (&cpy, -1.0);
	addEucVec (&cpy, &(candidateNeighbor->vecAddr), &cpy);

	dist = getEucVecMagnitude (&cpy);

	if (dist > ((kNNParams *) params)->searchRadius)
	{
		return;
	}

	for (i = 0; i < NUM_NEIGHBORS; i++)
	{
		if (workspace->neighbors[i] == NULL)
		{
			workspace->neighbors[i] = candidateNeighbor;
			workspace->dists[i] = dist;
			workspace->neighborCount += 1;
			break;
		}
		else if (dist < workspace->dists[i])
		{
			for (j = NUM_NEIGHBORS-1; j > i; j--)
			{
				workspace->neighbors[j] = workspace->neighbors[j-1];
				workspace->dists[j] = workspace->dists[j-1];
			}
			workspace->neighbors[i] = candidateNeighbor;
			workspace->dists[i] = dist;
			workspace->neighborCount = (workspace->neighborCount >= NUM_NEIGHBORS) ? (NUM_NEIGHBORS) : (workspace->neighborCount + 1);
			break;
		}
	}
}

void nodeCanAddrCheckCB (Node *curNd, unsigned int depth, void *params)
{
	fprintf(stdout, "%u\n", depth);
	printCanAddr(stdout, &(curNd->cAddr));
	fprintf(stdout, "\n");
	printCanAddr(stdout, &(curNd->parkedDPE->cAddr));
	fprintf(stdout, "\n");
	fprintf(stdout, "\n");
}

// TODO: this code is old, but may still be useful, requires cleanup though
/*
void smallestEnclosingTileCB (Node *curNd, unsigned int depth, void *params)
{
	unsigned int radius = ((kNNParams *)params)->radius;
	LatAddr extrema[8];

	unsigned int i;
	unsigned int j;

	unsigned int common_prefix_len = MAX_CAN_ADDR_LEN;

	for (i = 0; i < 8; i += 2)
	{
		extrema[i].a = (i == 0);
		extrema[i].b = (i == 2);
		extrema[i].c = (i == 4);
		extrema[i].d = (i == 6);

		scaleLatAddr((extrema+i), radius);
		addLatAddr((extrema+i), &(curNd->parkedDPE->lAddr), (extrema+i));

		extrema[i+1].a = (i == 0);
		extrema[i+1].b = (i == 2);
		extrema[i+1].c = (i == 4);
		extrema[i+1].d = (i == 6);

		scaleLatAddr((extrema+i+1), (-1)*radius);
		addLatAddr((extrema+i+1), &(curNd->parkedDPE->lAddr), (extrema+i+1));
	}

	
	for (i = 0; i < 8; i++)
	{
		CanAddr tmp;
		tmp.addrLen = MAX_CAN_ADDR_LEN;
		produceCanAddr((extrema+i), &tmp);

		for (j = 0; j < MAX_CAN_ADDR_LEN; j++)
		{
			if (curNd->parkedDPE->cAddr.addr[j].val != tmp.addr[j].val)
			{
				break;
			}
		}
		common_prefix_len = (common_prefix_len > j) ? (j) : (common_prefix_len);
	}

	Node *nd = ((kNNParams *)params)->rootNode;
	CanAddr *cAddr = &(curNd->parkedDPE->cAddr);

	for (i = 0; i < common_prefix_len; i++)
	{
		if (nd->children[cAddr->addr[i].val] != NULL)
		{
			nd = nd->children[cAddr->addr[i].val];
		}
	}

	fprintf(stdout, "%u\n", nd->population);
}
*/
