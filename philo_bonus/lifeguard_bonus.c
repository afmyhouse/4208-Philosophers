/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeguard_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:12:39 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 22:55:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_died(t_philo *p)
{
	if (sem_wait(p->info->sem_death) == 0)
	{
		if (set_time_sem(p) == 0)
		{
			if (utime(p->tnow) - utime(p->t0) > p->info->ttdie)
			{
				print_status(p, DEAD, p->tnow);
				p_finish(p);
				return (SUCCESS);
			}
		}
		if (sem_post(p->info->sem_death) != 0)
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
	if (sem_wait(p->info->sem_print) == 0)
	{
		if (state == FORK)
			printf("%lld %d has taken a fork\n", \
				dtime(p->info->tstart, t), p->id);
		else if (state == EAT)
			printf("%lld %d is eating\n", dtime(p->info->tstart, t), p->id);
		else if (state == SLEEP)
			printf("%lld %d is sleeping\n", dtime(p->info->tstart, t), p->id);
		else if (state == THINK)
			printf("%lld %d is thinking\n", dtime(p->info->tstart, t), p->id);
		else if (state == DEAD)
			printf("%lld %d died\n", dtime(p->info->tstart, t), p->id);
		if (sem_post(p->info->sem_print) != 0)
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

void	*lifeguard(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (check_died(p) != 0)
			return (NULL);
	}
	return (SUCCESS);
}

int	philo_kill(t_philo *p)
{
	int		i;
	t_philo	*tmp;

	tmp = p;
	i = p->info->phqty;
	while (i--)
		sem_wait(p->info->sem_end);
	while (tmp->next != NULL && tmp->next != p)
	{
		kill(tmp->pid, SIGKILL);
		tmp = tmp->next;
	}
	kill(tmp->pid, SIGKILL);
	return (SUCCESS);
}
