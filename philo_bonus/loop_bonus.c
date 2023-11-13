/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:46 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 13:13:47 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grab_fork(t_philo *p)
{
	if (sem_wait(p->d->sem_forks) == 0)
	{
		if (printstate(p, FORK, now(p)) == 1)
			return (1);
	}
	else
	{
		printf("Error: sem_wait (forks)\n");
		return (1);
	}
	return (0);
}

int	eat(t_philo *p)
{
	if (sem_wait(p->d->sem_death) == 0)
	{
		p->t0 = now(p);
		if (sem_post(p->d->sem_death) != 0)
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
	printstate(p, EATING, now(p));
	usleep(ft_min(p->d->t_eat, p->d->t_die));
	if (drop_fork(p) == 1 || drop_fork(p) == 1)
		return (1);
	if (p->d->cap != NULL && ++p->meals == *p->d->cap)
		sem_post(p->d->sem_end);
	return (0);
}

int	nap(t_philo *p)
{
	if (printstate(p, SLEEPING, now(p)) == 1)
		return (1);
	usleep(p->d->t_sleep);
	return (0);
}

int	think(t_philo *p)
{
	if (printstate(p, THINKING, now(p)) == 1)
		return (1);
	usleep(p->d->t_think);
	return (0);
}

int	philo_routine(t_philo *p)
{
	set_time(p);
	while (1)
	{
		if (p->d->n_philo < 2)
			continue ;
		sem_wait(p->d->sem_go);
		if (grab_fork(p) == 0 && grab_fork(p) == 0)
		{
			sem_post(p->d->sem_go);
			if (eat(p) == 1 || nap(p) == 1 || think(p) == 1)
				endr(p);
		}
		else
			endr(p);
	}
	return (0);
}
