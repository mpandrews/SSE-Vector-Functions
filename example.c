#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sse_vec.h"

int main()
{
	float a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float *b = a;
	float c[5];
	SSE_Vec_Mul(a, b, c, 5);

	for (int i = 0; i < 5; i++)
	{
		printf("%f ", c[i]);
	}
	printf("\n%f\n", SSE_Vec_MulSum(a, b, 5));
	return 0;
}
