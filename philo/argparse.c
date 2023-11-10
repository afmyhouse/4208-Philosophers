/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:28 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/10 12:44:49 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 			checks if the arguments are valid
/// @param argv		arguments to validate
/// @return			SUCCESS if arguments are valid, ERROR otherwise
int	valid_argv(char **argv)
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
				return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

int	valid_args(t_data *d)
{
	int	r;

	r = 0;
	if (d->qty < 1 || d->qty > INTMAX)// || d->qty < INTMIN)
		r = 1;
	if (d->t_die < 0 || d->t_die > INTMAX || d->t_die < INTMIN)
		r = 1;
	if (d->t_eat < 0 || d->t_eat > INTMAX || d->t_eat < INTMIN)
		r = 1;
	if (d->t_sleep < 0 || d->t_sleep > INTMAX || d->t_sleep < INTMIN)
		r = 1;
	if (d->cap != NULL && (*d->cap < 1 || *d->cap > INTMAX || *d->cap < INTMIN))
		r = 1;
	if (r == 1)
		printf("Error: invalid arguments\n");
	return (r);
}

t_data	*get_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_bzero(data, sizeof(t_data));
	data->qty = ft_long_atoi(argv[1]);
	data->t_die = ft_long_atoi(argv[2]);
	data->t_eat = ft_long_atoi(argv[3]);
	data->t_sleep = ft_long_atoi(argv[4]);
	data->end = 0;
	if (argv[5] != NULL)
	{
		data->cap = malloc(sizeof(long long));
		*data->cap = ft_long_atoi(argv[5]);
		data->end = 1 - data->qty;
	}
	if (valid_args(data) == 1 && datafree(data) == 0)
		return (NULL);
	data->t_die = data->t_die * 1000;
	data->t_eat = data->t_eat * 1000;
	data->t_sleep = data->t_sleep * 1000;
	if ((data->t_die - data->t_eat - data->t_sleep) / 2 > 0)
		data->t_think = (data->t_die - data->t_eat - data->t_sleep) / 2;
	return (data);
}
