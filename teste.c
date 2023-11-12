#include <stdio.h>

int main(void)
{
	printf("Hello, world!\n");
	char *f[10];
	char g[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	int i = 0;
	while ( i < 10)
	{
		printf("f[%d] = %p\n", i, f[i]);
		printf("g[%d] = %c\n", i, g[i]);
		f[i] = &g[i];
		i++;
	}

	i = 0;
	while ( i <  10)
	{
		printf("f[%d] = %p\n", i, f[i]);
		printf("g[%d] = %c\n", i, g[i]);
		i++;
	}

	return (0);
}