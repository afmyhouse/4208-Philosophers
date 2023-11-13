#include <unistd.h>
#include <stdio.h>

int main(void)
{
	float m[4][4];

	//ft_bzero(m, sizeof(m));
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;

	float *ptr[4][4];
	int i = 0;
	int j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ptr[i][j] = &m[i][j];
			printf("ptr[%d][%d] = %p\t", i, j, ptr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
		printf("\n");
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ptr[i][j] = &m[i][j];
			printf("ptr[%d][%d] = %.1f\t", i, j, m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}