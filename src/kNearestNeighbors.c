#include "utils/Utils.h"

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage is: %s inputFileName outputFileName\n", argv[0]);
		exit(-1);
	}

	FILE *inFile;
	inFile = fopen(argv[1], "r");

	FILE *outFile;
	outFile = fopen (argv[2], "w");

	if (inFile <= 0)
	{
		fprintf(stderr, "Unable to open input file.\n");
		exit(-1);
	}

	if (outFile <= 0)
	{
		fprintf(stderr, "Unable to open output file.\n");
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

	kNNParams params;
	params.searchRadius = 20;
	params.rootNode = rootNode;
	params.outputFile = outFile;

	nodeTraverse(rootNode, 0, &params, kNNCallBack);

	fclose (outFile);
}
