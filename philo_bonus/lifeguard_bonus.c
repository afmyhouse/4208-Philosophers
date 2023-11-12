/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeguard_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:51:32 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:16:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_offset(t_philo *p)
{
	int		i;
	t_philo	*tmp;

	if (gettimeofday(&p->info->offset, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (1);
	}
	i = p->info->phqty;
	tmp = p;
	while (i--)
	{
		tmp->t0 = p->info->offset;
		tmp = tmp->next;
	}
	return (0);
}

int	deathcheck(t_philo *p)
{
	if (sem_wait(p->info->sem_death) == 0)
	{
		if (set_time(p) == 0)
		{
			if (utime(p->t) - utime(p->t0) > p->info->ttdie)
			{
				printstate(p, 4, p->t);
				endr(p);
				return (0);
			}
		}
		if (sem_post(p->info->sem_death) != 0)
		{
			printf("Error: sem_post (sem_death)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: sem_wait (sem_death)\n");
		return (1);
	}
	return (0);
}

int	printstate(t_philo *p, int state, struct timeval t)
{
	if (sem_wait(p->info->sem_print) == 0)
	{
		if (state == FORK)
			printf("%lld %d has taken a fork\n", \
				deltatime(p->info->offset, t), p->id);
		else if (state == EAT)
			printf("%lld %d is eating\n", deltatime(p->info->offset, t), p->id);
		else if (state == SLEEP)
			printf("%lld %d is SLEEP\n", deltatime(p->info->offset, t), p->id);
		else if (state == THINK)
			printf("%lld %d is THINK\n", deltatime(p->info->offset, t), p->id);
		else if (state == DEAD)
			printf("%lld %d died\n", deltatime(p->info->offset, t), p->id);
		if (sem_post(p->info->sem_print) != 0)
		{
			printf("Error: sem_post (sem_print)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: sem_wait (sem_print)\n");
		return (1);
	}
	return (0);
}

void	*bigbrother(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (deathcheck(p) != 0)
			return (NULL);
	}
	return (0);
}
