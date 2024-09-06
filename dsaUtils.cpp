#include<cstdlib>
#include "dsaUtils.h"
#include<time.h>


void RandomizeData(int* a, int cnt, int min, int max)
{
	srand(time(NULL));
	int u;
	for (int i = 0; i < cnt; i++) {
		u = (int)(max - min)*(double)rand() / (double)(RAND_MAX + 1) + min;
		*(a + i) = u;
	}
}
