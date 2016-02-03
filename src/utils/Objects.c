/*
	This File defines the structs and types necessary for the project.
	NOTE: the structures and functions in this file are assuming 3D and Order 4
*/

#include "Utils.h"

void printEucVec (FILE* out, EucVec *vec)
{
	fprintf(out, "EucVec:(%g, %g, %g)", vec->x, vec->y, vec->z);
}

void scaleEucVec(EucVec* vec, double scale)
{
	vec->x *= scale;
	vec->y *= scale;
	vec->z *= scale;
}

// While it is funky, output can be the same location as either of the operators...
void addEucVec(EucVec* opA, EucVec* opB, EucVec* output)
{
	output->x = opA->x + opB->x;
	output->y = opA->y + opB->y;
	output->z = opA->z + opB->z;
} 

double getEucVecMagnitude (EucVec *vec)
{
	return sqrt((vec->x*vec->x) + (vec->y*vec->y) + (vec->z*vec->z));
}

bool eucVecsAreEqual (EucVec *opA, EucVec *opB)
{
	return (opA->x == opB->x &&
		opA->y == opB->y &&
		opA->z == opB->z);
}

void printLatAddr (FILE* out, LatAddr *lAddr)
{
	fprintf(out, "LatAddr:(%i, %i, %i, %i)", lAddr->a, lAddr->b, lAddr->c, lAddr->d);
}

void cleanupLatAddr (LatAddr *lAddr)
{
	int min = lAddr->a;
	min = (min < lAddr->b) ? (min) : (lAddr->b);
	min = (min < lAddr->c) ? (min) : (lAddr->c);
	min = (min < lAddr->d) ? (min) : (lAddr->d);

	lAddr->a -= min;
	lAddr->b -= min;
	lAddr->c -= min;
	lAddr->d -= min;
}

void scaleLatAddr (LatAddr *lAddr, int scale)
{
	lAddr->a *= scale;
	lAddr->b *= scale;
	lAddr->c *= scale;
	lAddr->d *= scale;

	cleanupLatAddr(lAddr);
}

// Just like the addEucVec function, output can be either operand
void addLatAddr (LatAddr *opA, LatAddr *opB, LatAddr *output)
{
	output->a = opA->a + opB->a;
	output->b = opA->b + opB->b;
	output->c = opA->c + opB->c;
	output->d = opA->d + opB->d;

	cleanupLatAddr(output);
}

double getLatAddrMagnitude (LatAddr *lAddr)
{
	EucVec tmp;
	evalBasisLinearCombo (lAddr->a, lAddr->b, lAddr->c, lAddr->d, &tmp);
	return getEucVecMagnitude(&tmp);
}

void applyBMatrixToLatAddr (LatAddr *inAddr, LatAddr *outAddr)
{
	outAddr->a = (2*inAddr->a)-(inAddr->d);
	outAddr->b = (2*inAddr->b)-(inAddr->a);
	outAddr->c = (2*inAddr->c)-(inAddr->b);
	outAddr->d = (2*inAddr->d)-(inAddr->c);

	cleanupLatAddr(outAddr);
}

void printTuple (FILE* out, Tuple *t) 
{
	fprintf(out, "%u, ", (t->val+15)%15);
}

void printCanAddr (FILE* out, CanAddr *cAddr)
{
	int i;
	for (i = 0; i < MAX_CAN_ADDR_LEN; i++)
	{
		printTuple(out, (cAddr->addr) + i);
	}
}

void printDataPointEntry (FILE *out, DataPointEntry *dpe)
{
	fprintf(out, "%u\n", dpe->id);
	printEucVec(out, &(dpe->vecAddr));
	fprintf(out, "\n");
	printLatAddr(out, &(dpe->lAddr));
	fprintf(out, "\n");
	printCanAddr(out, &(dpe->cAddr));
	fprintf(out, "\n");
}

