/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:28 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:39:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msec2usec(void *t)
{
	*(long long *)t = *(long long *)t * 1000;
}

int	invalid_info(t_info *d)
{
	if (d->phqty < 1 || d->phqty > INTMAX
		|| d->ttdie < 0 || d->ttdie > INTMAX || d->ttdie < INTMIN
		|| d->tteat < 0 || d->tteat > INTMAX || d->tteat < INTMIN
		|| d->ttslp < 0 || d->ttslp > INTMAX || d->ttslp < INTMIN
		|| (d->cap != NULL
			&& (*d->cap < 1 || *d->cap > INTMAX || *d->cap < INTMIN)))
	{
		printf("Error: invalid arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

t_info	*philo_info(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	ft_bzero(info, sizeof(t_info));
	info->phqty = ft_long_atoi(argv[PHQTY]);
	info->ttdie = ft_long_atoi(argv[TTDIE]);
	info->tteat = ft_long_atoi(argv[TTEAT]);
	info->ttslp = ft_long_atoi(argv[TTSLP]);
	info->end = 0;
	if (argv[MEALQTY] != NULL)
	{
		info->cap = malloc(sizeof(long long));
		*info->cap = ft_long_atoi(argv[MEALQTY]);
		info->end = 1 - info->phqty;
	}
	if (invalid_info(info) == ERROR && free_data(info) == SUCCESS)
		return (NULL);
	msec2usec(&info->ttdie);
	msec2usec(&info->tteat);
	msec2usec(&info->ttslp);
	if ((info->ttdie - info->tteat - info->ttslp) / 2 > 0)
		info->ttthk = (info->ttdie - info->tteat - info->ttslp) / 2;
	return (info);
}
