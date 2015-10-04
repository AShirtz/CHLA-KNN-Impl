#include "utils/Utils.h"

int main ()
{
	FILE *inFile;
	FILE *outFile;
	
	// TODO: make it so these are params, maybe getOpt()?
	inFile = fopen ("input/test_full_set.csv", "r");
	outFile = fopen ("target/processed_output", "w");

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
