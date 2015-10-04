#include <stdio.h>
#include "../utils/Utils.h"

int main () 
{
	fprintf(stdout, "Hello again world\n");
	EucVec v;
	v.x = 3.141592678;
	v.y = 7.28;
	v.z = 1.61;
	printEucVec(stdout, &v);
	fprintf(stdout, "\n");

	LatAddr l;
	l.a = 14;
	l.b = 7;
	l.c = 1;
	l.d = 0;
	printLatAddr(stdout, &l);
	fprintf(stdout, "\n");

	scaleEucVec(&v, 2.0);
	printEucVec(stdout, &v);
	fprintf(stdout, "\n");

	int i;
	for (i = 0; i < 4; i++) 
	{
		getBasisVector(i, &v, 1.0);
		printEucVec(stdout, &v);
		fprintf(stdout, " %g\n", getEucVecMagnitude(&v));
	} 

	evalBasisLinearCombo(0, 1.0, 0, 0, &v);
	printEucVec(stdout, &v);
	fprintf(stdout, " %g\n", getEucVecMagnitude(&v));

	return 0;
}
