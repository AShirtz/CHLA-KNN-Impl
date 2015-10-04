#include <stdio.h>
#include "../utils/Utils.h"

int main () 
{
	EucVec v;
	v.x = 435.2550048;
	v.y = 1415.979980;
	v.z = 77.70320129;
	printEucVec(stdout, &v);
	fprintf(stdout, "\n");

	double a[9];
	double sol[3];
	double b[] = {v.x, v.y, v.z};

	getBasisVectorMatrix(a,1.0);

	int i,j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			fprintf(stdout, "%g, ", a[(i*3)+j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
	
	gauss_eliminate(a, b, sol, 3);

	for (i = 0; i < 3; i++)
	{
		fprintf(stdout, "%g, ", sol[i]);
	}
	fprintf(stdout, "\n");
	EucVec u;

	evalBasisLinearCombo(sol[0], sol[1], sol[2], 0.0, &u);
	printEucVec(stdout, &u);
	fprintf(stdout, "\n");
	printEucVec(stdout, &v);
	
	fprintf(stdout, "\n");
	fprintf(stdout, "\n");

	LatAddr lAddr;
	produceLatAddr(&v, &lAddr);
	fprintf(stdout, "\n");
	fprintf(stdout, "\n");
/*
	lAddr.a = 1+1;
	lAddr.b = 1+0;
	lAddr.c = 0+3;
	lAddr.d = 3+1;
	printLatAddr(stdout, &lAddr);
	fprintf(stdout, "\n");
*/
	return 0;
}
