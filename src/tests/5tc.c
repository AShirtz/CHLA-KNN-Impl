#include "../utils/Utils.h"

int main ()
{
	FILE *inFile;
	inFile = fopen("input/test_input.csv", "r");

	int ret = 0;
	size_t len = 0;
	char *newBuf = NULL;

	unsigned int longest_addr_len = 0;
	unsigned int longest_id = 0;

	do
	{
		ret = getline(&newBuf, &len, inFile);
		if (ret > 0)
		{
			unsigned int id;
			EucVec v;
			LatAddr lAddr;
			CanAddr cAddr;
			cAddr.addrLen = MAX_CAN_ADDR_LEN;

			parseLine (newBuf, &v, &id);

			fprintf(stdout, "Runnin Datapoint: %u\n", id);
			printEucVec(stdout, &v);
			fprintf(stdout, "\n");

			produceLatAddr (&v, &lAddr);
			printLatAddr(stdout, &lAddr);
			fprintf(stdout, "\n");

			int tmp = 0;
			tmp = produceCanAddr(&lAddr, &cAddr);

			if (tmp > longest_addr_len)
			{
				longest_addr_len = tmp;
				longest_id = id;
			}

			printCanAddr(stdout, &cAddr);
			fprintf(stdout, "\nAddr Len: %u\n\n", tmp);
			fprintf(stdout, "\n");
		}
	} while (ret > 0);

	fprintf(stdout, "Longest Addr: %u\nID: %u", longest_addr_len, longest_id);
	fclose(inFile);

	return 0;
}
