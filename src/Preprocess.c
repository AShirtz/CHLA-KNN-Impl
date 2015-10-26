#include "utils/Utils.h"

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage is: %s inputFileName outputFIleName\n", argv[0]);
		exit(-1);
	}

	FILE *inFile;
	FILE *outFile;
	
	inFile = fopen (argv[1], "r");
	outFile = fopen (argv[2], "w");

	if (inFile <= 0)
	{
		fprintf(stderr, "Unable to open input file.\n");
	}

	if (outFile <= 0)
	{
		fprintf(stderr, "Unable to open output file.\n");
	}

	unsigned int longestAddr = 0;

	int ret = 0;
	size_t len = 0;
	char *newBuf = NULL;

	do
	{
		ret = getline(&newBuf, &len, inFile);
		if (ret > 0)
		{
			DataPointEntry dpe;

			parseLine(newBuf, &(dpe.vecAddr), &(dpe.id));

			EucVec vCpy = dpe.vecAddr;
			produceLatAddr (&vCpy, &(dpe.lAddr));

			unsigned int tmp;
			LatAddr lCpy = dpe.lAddr;
			tmp = produceCanAddr (&lCpy, &(dpe.cAddr));

			longestAddr = (longestAddr > tmp) ? (longestAddr) : (tmp);

			writeDataPointToFile (outFile, &dpe);
		}
	} while (ret > 0);

	fclose (inFile);
	fclose (outFile);

	fprintf(stdout, "Longest CanAddr: %u\n", longestAddr);

	return 0;
}
