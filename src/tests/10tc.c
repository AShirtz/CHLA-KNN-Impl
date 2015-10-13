#include "../utils/Utils.h"

int main ()
{
	int radius = 5;

	LatAddr lAddr;
	lAddr.a = 10;
	lAddr.b = 14;
	lAddr.c = 7;
	lAddr.d = 0;

	LatAddr cpy = lAddr;
	CanAddr cAddr;

	produceCanAddr(&cpy, &cAddr);

	LatAddr extrema[8];

	unsigned int i;

// Generate Extrema of Bounding Volume
	for (i = 0; i < 8; i += 2)
	{
		extrema[i].a = (i == 0);
		extrema[i].b = (i == 2);
		extrema[i].c = (i == 4);
		extrema[i].d = (i == 6);

		scaleLatAddr((extrema+i), radius);

		addLatAddr((extrema+i), &lAddr, (extrema+i));

		extrema[i+1].a = (i == 0);
		extrema[i+1].b = (i == 2);
		extrema[i+1].c = (i == 4);
		extrema[i+1].d = (i == 6);

		scaleLatAddr((extrema+i+1), (-1)*radius);
		addLatAddr((extrema+i+1), &lAddr, (extrema+i+1));
	}

	unsigned int common_prefix_len = MAX_CAN_ADDR_LEN;
	unsigned int j;

	for (i = 0; i < 8; i++)
	{
		CanAddr tmp;
		tmp.addrLen = MAX_CAN_ADDR_LEN;
printLatAddr(stdout, (extrema+i));
fprintf(stdout, "\n");
		produceCanAddr((extrema+i), &tmp);
printCanAddr(stdout, &tmp);
fprintf(stdout, "\n");
fprintf(stdout, "\n");

		for (j = 0; j < MAX_CAN_ADDR_LEN; j++)
		{
			if (cAddr.addr[j].val != tmp.addr[j].val)
			{
				break;
			}
		}
		common_prefix_len = (common_prefix_len > j) ? (j) : (common_prefix_len);
	}

	fprintf(stdout, "CPL: %u\n", common_prefix_len);

	return 0;
}
