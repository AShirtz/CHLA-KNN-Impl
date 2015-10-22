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

	kNNParams params;
	params.radius = 15;
	params.rootNode = rootNode;

	nodeTraverse(rootNode, 0, &params, kNNCallBack);

	fclose (inFile);
}
