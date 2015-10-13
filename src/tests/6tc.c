#include "../utils/Utils.h"

int main ()
{
	FILE *inFile;
	inFile = fopen("input/test_input.csv", "r");

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
dpe.id = 0;

dpe.vecAddr.x = 0;
dpe.vecAddr.y = 0;
dpe.vecAddr.z = 0;

dpe.lAddr.a = 0;
dpe.lAddr.b = 0;
dpe.lAddr.c = 0;
dpe.lAddr.d = 0;

for (int i = 0; i < MAX_CAN_ADDR_LEN; i++)
{ dpe.cAddr.addr[i].val = 0; }

			printDataPointEntry(stdout, &dpe);
			fprintf(stdout, "\n\n");

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
