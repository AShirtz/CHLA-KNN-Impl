#include "Utils.h"


/*
	Tree Functions
*/

void allocateChild (Node *curNd, Tuple tup)
{
	if (curNd->children[tup.val] == NULL)
	{
		curNd->children[tup.val] = calloc(1, sizeof(Node));
	}
}

void nodeInsert (Node *curNd, DataPointEntry *dpe, unsigned int depth)
{
	if (depth > MAX_CAN_ADDR_LEN)
	{
		// TODO: error out
	}

	curNd->population += 1;
	if 	(curNd->population == 1)	{ curNd->parkedDPE = dpe; }
	else if	(curNd->population == 2)
	{
		allocateChild	(curNd, curNd->parkedDPE->cAddr.addr[depth]);
		nodeInsert	(curNd->children[curNd->parkedDPE->cAddr.addr[depth].val], curNd->parkedDPE, depth + 1);
		curNd->parkedDPE = NULL;
		allocateChild	(curNd, dpe->cAddr.addr[depth]);
		nodeInsert	(curNd->children[dpe->cAddr.addr[depth].val], dpe, depth + 1);
	}
	else
	{
		allocateChild	(curNd, dpe->cAddr.addr[depth]);
		nodeInsert	(curNd->children[dpe->cAddr.addr[depth].val], dpe, depth + 1);
	}
}

void nodeTraverse (Node *curNd, unsigned int depth, void *params, pFuncCB *callBack)
{
	if (curNd->parkedDPE != NULL)
	{
		callBack(curNd, depth, params);
	}
	else
	{
		int i;
		for (i = 0; i < 15; i++)
		{
			if (curNd->children[i] != NULL)
			{
				nodeTraverse (curNd->children[i], depth + 1, params, callBack);
			}
		}
	}
}

/*	Basis Vectors	*/

void getBasisVector (int index, EucVec* output, double scale)
{
	switch (index)
	{
		case 0:
			output->x = 0;
			output->y = 0;
			output->z = 1;
			break;
		case 1:
			output->x = -(sqrt(2.0)/3.0);
			output->y = -(sqrt(2.0/3.0));
			output->z = -(1.0/3.0);
			break;
		case 2:
			output->x = -(sqrt(2.0)/3.0);
			output->y = sqrt(2.0/3.0);
			output->z = -(1.0/3.0);
			break;
		case 3:
			output->x = (2.0/3.0)*sqrt(2.0);
			output->y = 0;
			output->z = -(1.0/3.0);
			break;
		default:
		//TODO: ERROR
			return;
	}
	scaleEucVec(output, scale);
}

void evalBasisLinearCombo (double a, double b, double c, double d, EucVec* output)
{
	EucVec tmp;
	getBasisVector(0, &tmp, a);
	memcpy((void *) output, (void *) &tmp, sizeof(EucVec));
	getBasisVector(1, &tmp, b);
	addEucVec(&tmp, output, output);
	getBasisVector(2, &tmp, c);
	addEucVec(&tmp, output, output);
	getBasisVector(3, &tmp, d);
	addEucVec(&tmp, output, output);
}

#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))

// This method is assuming a lot of things, should be wary of it
//  a must have 9 slots for doubles...
void getBasisVectorMatrix (double* a, double scale)
{
	EucVec tmp;
	int i;
	for (i = 0; i < 3; i++)
	{
		getBasisVector(i, &tmp, scale);
		*mat_elem(a, 0, i, 3) = tmp.x;
		*mat_elem(a, 1, i, 3) = tmp.y;
		*mat_elem(a, 2, i, 3) = tmp.z;
	}
}

void swap_row(double *a, double *b, int r1, int r2, int n)
{
	double tmp, *p1, *p2;
	int i;
 
	if (r1 == r2) return;
	for (i = 0; i < n; i++) {
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	}
	tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}
 
void gauss_eliminate(double *a, double *b, double *x, int n)
{
#define A(y, x) (*mat_elem(a, y, x, n))
	int i, j, col, row, max_row,dia;
	double max, tmp;
 
	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);
 
		for (row = dia + 1; row < n; row++)
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;
 
		swap_row(a, b, dia, max_row, n);
 
		for (row = dia + 1; row < n; row++) {
			tmp = A(row, dia) / A(dia, dia);
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	for (row = n - 1; row >= 0; row--) {
		tmp = b[row];
		for (j = n - 1; j > row; j--)
			tmp -= x[j] * A(row, j);
		x[row] = tmp / A(row, row);
	}
#undef A
}

// REDUX
// This method assumes that getBasisVectorMatrix uses the first 3 vectors from the basis vector set
void produceLatAddr (EucVec *inVec, LatAddr *outAddr)
{
	double a[9];
	double sol[3];
	double b[] = {inVec->x, inVec->y, inVec->z};

	getBasisVectorMatrix(a, 1.0);
	gauss_eliminate(a, b, sol, 3);

	int i;
	int min = 0;
	for (i = 0; i < 3; i++)
	{
		min = (round(sol[i]) < min ? (round(sol[i])) : (min));
	}

	outAddr->a = round(sol[0]) - min;
	outAddr->b = round(sol[1]) - min;
	outAddr->c = round(sol[2]) - min;
	outAddr->d = -min;
}

// NOTE: this modifies inAddr in place
// This is from the paper "An Isomorpnism..." section 5.5 (2)
unsigned int produceCanAddr (LatAddr *inAddr, CanAddr *outAddr)
{
	Tuple cur;
	unsigned int i;

	for (i = 0; i < MAX_CAN_ADDR_LEN; i++)
	{
		outAddr->addr[i].val = 0;
	}

	i = 0;

	while ((inAddr->a != inAddr->b || inAddr->a != inAddr->c || inAddr->a != inAddr->d) && i <= MAX_CAN_ADDR_LEN)
	{
		i++;
		cur.val =  (inAddr->a + (2 * inAddr->b) + (4 * inAddr->c) + (8 * inAddr->d)) % 15;
		outAddr->addr[MAX_CAN_ADDR_LEN - (i)] = cur;

		inAddr->a = inAddr->a - (cur.val & 1);
		inAddr->b = inAddr->b - ((cur.val >> 1) & 1);
		inAddr->c = inAddr->c - ((cur.val >> 2) & 1);
		inAddr->d = inAddr->d - ((cur.val >> 3) & 1);

		int a = inAddr->a;
		int b = inAddr->b;
		int c = inAddr->c;
		int d = inAddr->d;

		inAddr->a = ((8*a) + (1*b) + (2*c) + (4*d))/15;
		inAddr->b = ((4*a) + (8*b) + (1*c) + (2*d))/15;
		inAddr->c = ((2*a) + (4*b) + (8*c) + (1*d))/15;
		inAddr->d = ((1*a) + (2*b) + (4*c) + (8*d))/15;
	}
	return i;
}
