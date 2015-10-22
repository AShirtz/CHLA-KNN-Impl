#include "utils/Utils.h"

int main ()
{
	LatAddr lAddr;
	lAddr.a = 14;
	lAddr.b = 7;
	lAddr.c = 0;
	lAddr.d = 3;

	LatAddr cpy = lAddr;

	CanAddr cAddr;
	produceCanAddr(&cpy, &cAddr);

printCanAddr(stdout, &cAddr);
fprintf(stdout, "\n");
	convertCanAddrToLatAddr (&cAddr, &cpy);

printLatAddr(stdout, &lAddr);
fprintf(stdout, "\n");
printLatAddr(stdout, &cpy);
fprintf(stdout, "\n");

	return 0;
}
