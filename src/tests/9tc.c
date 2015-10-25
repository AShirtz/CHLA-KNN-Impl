#include "../utils/Utils.h"

int main ()
{
	FILE *inFile;
	inFile = fopen("target/processed_output", "r");

	if (inFile <= 0)
	{
		fprintf(stderr, "No Input File\n");
		exit(-1);
	}

	int ret = 0;
	
	Node *rootNode;
	rootNode = calloc(1, sizeof(Node));

	CanAddr tmp;
	int i;
	
	for (i = 0; i < MAX_CAN_ADDR_LEN; i++)
	{
		tmp.addr[i].val = 0;
	}

	rootNode->cAddr = tmp;

	do
	{
		DataPointEntry *dpe;
		dpe = calloc(1, sizeof(DataPointEntry));
		ret = readDataPointFromFile (inFile, dpe);

		if (ret > 0)
		{
			nodeInsert (rootNode, dpe, 0);
		}
	} while (ret > 0);

	fclose (inFile);

	FILE *outFile;
	outFile = fopen ("target/kNN_output", "w");

	kNNParams params;
	params.searchRadius = 20;
	params.rootNode = rootNode;
	params.outputFile = outFile;

	nodeTraverse(rootNode, 0, &params, kNNCallBack);
}
