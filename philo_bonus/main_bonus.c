/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:27 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 13:46:19 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	invalid_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
	return (0);
}

static int	invalid_argv(char **argv)
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

int	datacheck(t_data *info)
{
	int	r;

	r = 0;
	if (info->n_philo < 1 || info->n_philo > INTMAX || info->n_philo < INTMIN)
		r = 1;
	if (info->t_die < 0 || info->t_die > INTMAX || info->t_die < INTMIN)
		r = 1;
	if (info->t_eat < 0 || info->t_eat > INTMAX || info->t_eat < INTMIN)
		r = 1;
	if (info->t_sleep < 0 || info->t_sleep > INTMAX || info->t_sleep < INTMIN)
		r = 1;
	if (info->cap != NULL && (*info->cap < 1 || *info->cap > INTMAX || *info->cap < INTMIN))
		r = 1;
	if (r == 1)
		printf("Error: invalid arguments\n");
	return (r);
}

t_data	*get_data(char **argv)
{
	t_data	*info;

	info = malloc(sizeof(t_data));
	ft_bzero(info, sizeof(t_data));
	info->n_philo = ft_long_atoi(argv[1]);
	info->t_die = ft_long_atoi(argv[2]);
	info->t_eat = ft_long_atoi(argv[3]);
	info->t_sleep = ft_long_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		info->cap = malloc(sizeof(long long));
		*info->cap = ft_long_atoi(argv[5]);
	}
	if (datacheck(info) == 1 && datafree(info) == 0)
		return (NULL);
	info->t_die = info->t_die * 1000;
	info->t_eat = info->t_eat * 1000;
	info->t_sleep = info->t_sleep * 1000;
	if (info->n_philo % 2 && (info->t_die - info->t_eat - info->t_sleep) / 2 > 0)
		info->t_think = (info->t_die - info->t_eat - info->t_sleep) / 2;
	return (info);
}

int	main(int argc, char **argv)
{
	t_data	*d;
	t_philo	*p;

	if (invalid_argc(argc) == 1 || invalid_argv(argv) == 1)
		return (1);
	d = get_data(argv);
	if (!d)
		return (1);
	p = philo_init(d);
	if (!p)
		return (1);
	if (seminit(d) == 1 || set_processes(p) == 1)
	{
		philofree(p);
		return (1);
	}
	philo_waiter(p);
	semdestroyer(d);
	philofree(p);
	return (0);
}
