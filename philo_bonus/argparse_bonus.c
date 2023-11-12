
#include "philo_bonus.h"

int	invalid_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
	return (0);
}

int	invalid_argv(char **argv)
{
	int		i;
	char	*t;
	int		sign;

	i = 0;
	while (argv[++i])
	{
		t = argv[i];
		sign = 1;
		while (*t)
		{
			if (((*t == '-' || *t == '+') && sign) || (*t >= '0' && *t <= '9'))
			{
				sign = 0;
				t++;
			}
			else
			{
				printf("Error: invalid arguments\n");
				return (1);
			}
		}
	}
	return (0);
}

int	invalid_info(t_info *d)
{
	int	r;

	r = 0;
	if (d->phqty < 1 || d->phqty > INTMAX)// || d->n_philo < INTMIN)
		r = 1;
	if (d->ttdie < 0 || d->ttdie > INTMAX || d->ttdie < INTMIN)
		r = 1;
	if (d->tteat < 0 || d->tteat > INTMAX || d->tteat < INTMIN)
		r = 1;
	if (d->ttslp < 0 || d->ttslp > INTMAX || d->ttslp < INTMIN)
		r = 1;
	if (d->cap != NULL && (*d->cap < 1 || *d->cap > INTMAX || *d->cap < INTMIN))
		r = 1;
	if (r == 1)
		printf("Error: invalid arguments\n");
	return (r);
}

t_info	*info_init(char **argv)
{
	t_info	*d;

	d = malloc(sizeof(t_info));
	ft_bzero(d, sizeof(t_info));
	d->phqty = ft_long_atoi(argv[1]);
	d->ttdie = ft_long_atoi(argv[2]);
	d->tteat = ft_long_atoi(argv[3]);
	d->ttslp = ft_long_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		d->cap = malloc(sizeof(long long));
		*d->cap = ft_long_atoi(argv[5]);
	}
	if (invalid_info(d) == 1 && free_data(d) == 0)
		return (NULL);
	d->ttdie = d->ttdie * 1000;
	d->tteat = d->tteat * 1000;
	d->ttslp = d->ttslp * 1000;
	if (d->phqty % 2 && (d->ttdie - d->tteat - d->ttslp) / 2 > 0)
		d->ttthk = (d->ttdie - d->tteat - d->ttslp) / 2;
	return (d);
}
