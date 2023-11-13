/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:46 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:07:59 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	grab_fork(t_philo *p)
{
	if (sem_wait(p->d->sem_forks) == 0)
	{
		if (print_status(p, FORK, now(p)) == 1)
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
	print_status(p, EAT, now(p));
	usleep(ft_min(p->d->tteat, p->d->ttdie));
	if (drop_fork(p) == 1 || drop_fork(p) == 1)
		return (1);
	if (p->d->eatqty != NULL && ++p->meals == *p->d->eatqty)
		sem_post(p->d->sem_end);
	return (0);
}

int	nap(t_philo *p)
{
	if (print_status(p, SLEEP, now(p)) == 1)
		return (1);
	usleep(p->d->ttslp);
	return (0);
}

int	think(t_philo *p)
{
	if (print_status(p, THINK, now(p)) == 1)
		return (1);
	usleep(p->d->ttthk);
	return (0);
}

int	philo_routine(t_philo *p)
{
	set_time(p);
	while (1)
	{
		if (p->d->phqty < 2)
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
