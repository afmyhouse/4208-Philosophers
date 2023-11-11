/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:44:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:40:21 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(int id, t_info *info)
{
	t_philo	*p;
	t_fork	f[2];

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	ft_bzero(p, sizeof(t_philo));
	ft_bzero(f, sizeof(t_fork) * 2);
	p->id = id;
	p->d = info;
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
			philo_free(p, NULL);
			free_data(info);
			return (NULL);
		}
		philo_add(&p, new);
	}
	return (p);
}

int	set_threads(t_philo *p)
{
	t_philo	*tmp;

	tmp = p;
	while (tmp->next != NULL && tmp->next != p)
	{
		if (pthread_create(&tmp->thread, NULL, philo_routine, (void *)tmp) != 0)
		{
			printf("Error: pthread_create\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	if (pthread_create(&tmp->thread, NULL, philo_routine, (void *)tmp) != 0)
	{
		printf("Error: pthread_create\n");
		return (1);
	}
	return (0);
}
