#include "FileIO.h"

void parseLine (char *inputLine, EucVec *outVec, unsigned int *id)
{
	char *delim = ",";
	char *out;
	outVec->x = atof(strtok(inputLine, delim));
	outVec->y = atof(strtok(NULL, delim));
	outVec->z = atof(strtok(NULL, delim));
	*id = atoi(strtok(NULL, delim));
}

unsigned int writeDataPointToFile (FILE *out, DataPointEntry *dpe)
{
	return fwrite (dpe, sizeof(DataPointEntry), 1, out);
}

unsigned int readDataPointFromFile (FILE *in, DataPointEntry *dpe)
{
	return fread (dpe, sizeof(DataPointEntry), 1, in);
}
