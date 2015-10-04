#include "../utils/Utils.h"

int main ()
{
	EucVec v;
	char in[80] = "435.2550048828;1415.9799804688;77.7032012939;0";
	unsigned int id;
	parseLine(in, &v, &id);
	printEucVec(stdout, &v);
	fprintf(stdout, "\n%u\n", id);


	FILE *inFile;
	inFile = fopen("input/test_input.csv", "r");
	char buf[100];
	int ret;
fprintf(stdout, "inputFile: %u\n", inFile);
	ret = fread(buf, 1, 99, inFile);
	fprintf(stdout, "%u: %s\n\n", ret, buf);
	fclose(inFile);


	ret = 0;
	size_t len = 0;
	char *newBuf = NULL;
	inFile = fopen("input/test_input.csv", "r");
	ret = getline(&newBuf, &len, inFile);
	fprintf(stdout, "%s\n", newBuf);

	parseLine(newBuf, &v, &id);
	printEucVec(stdout, &v);

	fprintf(stdout, "\n%u\n", id);

	return 0;
}
