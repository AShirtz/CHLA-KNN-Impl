/*
	This File defines the structs and types necessary for the project.
	NOTE: the structures and functions in this file are assuming 3D and Order 4
*/

#ifndef OBJECTS_H
#define OBJECTS_H

#include "Utils.h"

/*
	DATA STRUCTURES	
*/

typedef struct 
{
	double x;
	double y;
	double z;
} EucVec;

void printEucVec 		(FILE* out, EucVec *vec);
void scaleEucVec		(EucVec* vec, double scale);
void addEucVec			(EucVec* opA, EucVec* opB, EucVec* output);
double getEucVecMagnitude 	(EucVec * vec);

typedef struct
{
	int a;
	int b;
	int c;
	int d;
} LatAddr;

void printLatAddr 		(FILE* out, LatAddr *lAddr);
void cleanupLatAddr 		(LatAddr *lAddr);
void scaleLatAddr 		(LatAddr *lAddr, int scale);
void addLatAddr 		(LatAddr *opA, LatAddr *opB, LatAddr *output);
void applyBMatrixToLatAddr 	(LatAddr *inAddr, LatAddr *outAddr);

typedef struct
{
	unsigned int val : 4;
} Tuple;

void printTuple		(FILE* out, Tuple *t);

typedef struct
{
	unsigned int addrLen;
	Tuple addr[MAX_CAN_ADDR_LEN];
} CanAddr;

void printCanAddr 	(FILE* out, CanAddr *cAddr);

typedef struct
{
	unsigned int 	id;
	EucVec		vecAddr;
	LatAddr		lAddr;
	CanAddr 	cAddr;
} DataPointEntry;

void printDataPointEntry (FILE *out, DataPointEntry *dpe);

typedef struct TreeNode
{
	DataPointEntry *parkedDPE;
	unsigned int population;
	struct TreeNode *children[15];
} Node;

#endif
