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
