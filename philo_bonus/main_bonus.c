/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:27 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:00:50 by antoda-s         ###   ########.fr       */
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

/// @brief 		Check validity the TTDIE, TTEAT, TTSLP, PHQTY parameters
/// @param info	Pointer to the t_info structure
/// @return		SUCCESS if parameters are valid, ERROR otherwise
int	invalid_info(t_info *info)
{
	if (info->phqty < 1 || info->phqty > INTMAX// || info->phqty < INTMIN
		|| info->ttdie < 0 || info->ttdie > INTMAX || info->ttdie < INTMIN
		|| info->tteat < 0 || info->tteat > INTMAX || info->tteat < INTMIN
		|| info->ttslp < 0 || info->ttslp > INTMAX || info->ttslp < INTMIN
		|| (info->eatqty != NULL
			&& (*info->eatqty < 1 || *info->eatqty > INTMAX || *info->eatqty < INTMIN)))
	{
		printf("Error: invalid arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

t_info	*get_data(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	ft_bzero(info, sizeof(t_info));
	info->phqty = ft_long_atoi(argv[1]);
	info->ttdie = ft_long_atoi(argv[2]);
	info->tteat = ft_long_atoi(argv[3]);
	info->ttslp = ft_long_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		info->eatqty = malloc(sizeof(long long));
		*info->eatqty = ft_long_atoi(argv[5]);
	}
	if (invalid_info(info) == 1 && free_data(info) == 0)
		return (NULL);
	info->ttdie = info->ttdie * 1000;
	info->tteat = info->tteat * 1000;
	info->ttslp = info->ttslp * 1000;
	if (info->phqty % 2 && (info->ttdie - info->tteat - info->ttslp) / 2 > 0)
		info->ttthk = (info->ttdie - info->tteat - info->ttslp) / 2;
	return (info);
}

int	main(int argc, char **argv)
{
	t_info	*d;
	t_philo	*p;

	if (invalid_argc(argc) == 1 || invalid_argv(argv) == 1)
		return (1);
	d = get_data(argv);
	if (!d)
		return (1);
	p = init_philo(d);
	if (!p)
		return (1);
	if (init_semaphore(d) == 1 || set_processes(p) == 1)
	{
		free_philo(p);
		return (1);
	}
	philo_waiter(p);
	semdestroyer(d);
	free_philo(p);
	return (0);
}
