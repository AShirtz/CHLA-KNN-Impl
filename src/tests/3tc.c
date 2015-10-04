#include <stdio.h>
#include "../utils/Utils.h"

int main ()
{
	EucVec v;
	v.x = 435.2550048;
	v.y = 1415.979980;
	v.z = 77.70320129;

	LatAddr lAddr;
	produceLatAddr(&v, &lAddr);

	printEucVec(stdout, &v);
	fprintf(stdout, "\n");
	printLatAddr(stdout, &lAddr);
	fprintf(stdout, "\n");

	return 0;
}
