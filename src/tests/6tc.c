#include "../utils/Utils.h"

int main ()
{
	FILE *inFile;
	inFile = fopen("input/test_full_set.csv", "r");

	FILE *outFile;
	outFile = fopen("target/test_output", "w");

	unsigned int longestAddr = 0;

	int ret = 0;
	size_t len = 0;
	char *newBuf = NULL;

	do
	{
		ret = getline(&newBuf, &len, inFile);
		if (ret > 0)
		{
			EucVec v;
			LatAddr lAddr;
			DataPointEntry dpe;

			parseLine (newBuf, &v, &(dpe.id));

			produceLatAddr (&v, &lAddr);

			unsigned int tmp;
			tmp = produceCanAddr(&lAddr, &(dpe.cAddr));

			longestAddr = (longestAddr > tmp ? longestAddr : tmp);

			writeDataPointToFile (outFile, &dpe);
			printDataPointEntry(stdout, &dpe);
			fprintf(stdout, "\n\n");
		}
	} while (ret > 0);

	fprintf(stdout, "Longest Addr: %u\n", longestAddr);

	fclose(inFile);
	fclose(outFile);

	return 0;
}
