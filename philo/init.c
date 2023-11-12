/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:44:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 19:33:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(int id, t_info *info)
{
	t_philo	*p;
	//t_fork	f[2];

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	ft_bzero(p, sizeof(t_philo));
	//ft_bzero(f, sizeof(t_fork) * 2);
	p->id = id;
	p->info = info;
	if (info->phqty > 2 && id % 2 == 0)
		p->go = 1;
	return (p);
}

void	philo_add(t_philo **p, t_philo *new)
{
	t_philo	*tmp;

	if (!*p)
	{
		*p = new;
		return ;
	}
	tmp = *p;
	while (tmp->id != new->id - 1)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = *p;
	(*p)->prev = new;
}

t_philo	*philo_init(t_info *info)
{
	int		i;
	t_philo	*p;
	t_philo	*new;

	p = NULL;
	new = NULL;
	i = 0;
	while (++i <= info->phqty)
	{
		new = philo_new(i, info);
		if (!new)
		{
			free_philo(p, NULL);
			free_data(info);
			return (NULL);
		}
		philo_add(&p, new);
	}
	return (p);
}

t_info	*info_init(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	ft_bzero(info, sizeof(t_info));
	info->phqty = ft_long_atoi(argv[PHQTY]);
	info->ttdie = ft_long_atoi(argv[TTDIE]);
	info->tteat = ft_long_atoi(argv[TTEAT]);
	info->ttslp = ft_long_atoi(argv[TTSLP]);
	if (argv[MEALQTY] != NULL)
	{
		info->mealqty = malloc(sizeof(long long));
		*info->mealqty = ft_long_atoi(argv[MEALQTY]);
		info->end = 1 - info->phqty;
	}
	if (invalid_info(info) == ERROR && free_data(info) == SUCCESS)
		return (NULL);
	ft_msec2usec(&info->ttdie);
	ft_msec2usec(&info->tteat);
	ft_msec2usec(&info->ttslp);
	if ((info->ttdie - info->tteat - info->ttslp) / 2 > 0)
		info->ttthk = (info->ttdie - info->tteat - info->ttslp) / 2;
	return (info);
}

t_fork	*fork_init(t_philo *p)
{
	t_fork	*f;
	int		i;

	f = malloc(sizeof(t_fork) * p->info->phqty);
	if (!f)
		return (NULL);
	ft_bzero(f, sizeof(t_fork) * p->info->phqty);
	i = 0;
	while (++i <= p->info->phqty)
	{
		f[i - 1].mtx = malloc(sizeof(pthread_mutex_t));
		if (!f[i - 1].mtx)
		{
			free_philo(p, f);
			return (NULL);
		}
		if (pthread_mutex_init(f[i - 1].mtx, NULL) != 0)
		{
			printf("Error: pthread_mutex_init\n");
			free_philo(p, f);
			return (NULL);
		}
		f[i - 1].id = i;
	}
	return (f);
}
