/*
	This file contains the functions for interacting with input and output files
	as well as functions for parsing input.
*/

#ifndef DENSITY_FILEIO_H
#define DENSITY_FILEIO_H

#include "Utils.h"

void parseLine (char *inputLine, EucVec *outVec, unsigned int *id);

unsigned int writeDataPointToFile (FILE *out, DataPointEntry *dpe);

unsigned int readDataPointFromFile (FILE *in, DataPointEntry *dpe);

#endif
