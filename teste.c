#include <stdio.h>

int main(void)
{
	printf("Hello, world!\n");
	int *f[10];
	int g[10] = {1,2,3,4,5,6,7,8,9,10};

	int i = 1;
	while ( i <= 10)
	{
		printf("f[%d] = %ls\n", i, f[i]);
		printf("g[%d] = %d\n", i, g[i]);
		f[(i - 1) % 2] = &g[i - 1];
		f[i % 2] = &g[i];
		i++;
	}

	i = 1;
	while ( i <= 10)
	{
		printf("f[%d] = %ls\n", i, f[i]);
		printf("g[%d] = %d\n", i, g[i]);
		i++;
	}

	return (0);
}