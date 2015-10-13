#include "../utils/Utils.h"

int main ()
{
	FILE *inFile;
	inFile = fopen("target/test_output", "r");

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
		ret = readDataPointFromFile(inFile, dpe);
		if (ret > 0)
		{
			nodeInsert(rootNode, dpe, 0);
		}
	} while (ret > 0);

	fclose(inFile);

	return 0;
}
