/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:04 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:03:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_fork(t_philo *p, int fork_id)
{
	struct timeval	t;
	int				status;

	status = 0;
	while (forkcheck(p, fork_id, 0) != 0)
		status = deathcheck(p, &t);
	if (endcheck(p) == -1)
		return (status);
	if (pthread_mutex_lock(p->f[fork_id]->mtx) == 0)
	{
		forkupdate(p, fork_id, p->id);
		if (deathcheck(p, &t) == 1 || printstate(p, FORK, t) == 1)
		{
			if (pthread_mutex_unlock(p->f[fork_id]->mtx) != 0)
				printf("Error: pthread_mutex_unlock (fork)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (fork)\n");
		return (1);
	}
	return (status);
}

int	eat(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = deathcheck(p, &t);
	if (endcheck(p) == -1)
		return (status);
	if (status == 0)
	{
		p->t0 = t;
		printstate(p, EAT, t);
		usleep(ft_min(p->d->tteat, p->d->ttdie));
		if (p->d->cap != NULL && ++p->meals == *p->d->cap)
			endset(p, EAT);
	}
	if (drop_fork(p, 0) == 1 || drop_fork(p, 1) == 1)
		return (1);
	return (status);
}

int	nap(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = deathcheck(p, &t);
	if (endcheck(p) == -1)
		return (status);
	if (status == 0)
	{
		if (printstate(p, SLEEP, t) == 1)
			return (1);
		if (p->d->ttslp + p->d->tteat < p->d->ttdie)
			usleep(p->d->ttslp);
		else
			usleep(p->d->ttdie - p->d->tteat);
	}
	return (deathcheck(p, &t));
}

int	think(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = deathcheck(p, &t);
	if (endcheck(p) == -1)
		return (status);
	if (status == 1 || printstate(p, THINK, t) == 1)
		return (1);
	usleep(p->d->ttthk);
	return (0);
}

void	*philo_routine(void *philo)
{
	t_philo			*p;
	struct timeval	t;

	p = (t_philo *)philo;
	set_offset(philo);
	while (1)
	{
		if (deathcheck(philo, &t) == 1 || endcheck(p) == -1)
		{
			drop_fork(p, 0);
			drop_fork(p, 1);
			return (NULL);
		}
		if (p->f[1] == NULL || (forkcheck(p, 0, 0) == 0 && p->go == 1))
			continue ;
		p->go = 0;
		if (grab_fork(philo, 0) == 0 && grab_fork(philo, 1) == 0)
		{
			if (eat(philo) == 1 || nap(philo) == 1 || think(philo) == 1)
				return (NULL);
		}
		else
			return (NULL);
	}
	return (NULL);
}
