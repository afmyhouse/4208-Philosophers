/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeguard_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:12:39 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:13:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_offset(t_philo *p)
{
	int		i;
	t_philo	*tmp;


	// if (p->info->offset.tv_sec == 0)
	// 	set_time(&p->info->offset);
	if (gettimeofday(&p->d->offset, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (ERROR);
	}
	i = p->d->phqty;
	tmp = p;
	while (i--)
	{
		tmp->t0 = p->d->offset;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_died(t_philo *p)
{
	if (sem_wait(p->d->sem_death) == 0)
	{
		if (set_time(p) == 0)
		{
			if (utime(p->t) - utime(p->t0) > p->d->ttdie)
			{
				print_status(p, 4, p->t);
				endr(p);
				return (SUCCESS);
			}
		}
		if (sem_post(p->d->sem_death) != 0)
		{
			printf("Error: sem_post (sem_death)\n");
			return (ERROR);
		}
	}
	else
	{
		printf("Error: sem_wait (sem_death)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	print_status(t_philo *p, int state, struct timeval t)
{
	if (sem_wait(p->d->sem_print) == 0)
	{
		if (state == FORK)
			printf("%lld %d has taken a fork\n", \
				dtime(p->d->offset, t), p->id);
		else if (state == EAT)
			printf("%lld %d is eating\n", dtime(p->d->offset, t), p->id);
		else if (state == SLEEP)
			printf("%lld %d is sleeping\n", dtime(p->d->offset, t), p->id);
		else if (state == THINK)
			printf("%lld %d is thinking\n", dtime(p->d->offset, t), p->id);
		else if (state == DEAD)
			printf("%lld %d died\n", dtime(p->d->offset, t), p->id);
		if (sem_post(p->d->sem_print) != 0)
		{
			printf("Error: sem_post (sem_print)\n");
			return (ERROR);
		}
	}
	else
	{
		printf("Error: sem_wait (sem_print)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	*bigbrother(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (check_died(p) != 0)
			return (NULL);
	}
	return (0);
}
