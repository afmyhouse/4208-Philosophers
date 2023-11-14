/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:46 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 18:36:31 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	p_eat(t_philo *p)
{
	if (sem_wait(p->d->sem_death) == 0)
	{
		p->t0 = now(p);
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
	print_status(p, EAT, now(p));
	usleep(ft_min(p->d->tteat, p->d->ttdie));
	if (fork_drop(p) == 1 || fork_drop(p) == 1)
		return (ERROR);
	if (p->d->eatqty != NULL && ++p->meals == *p->d->eatqty)
		sem_post(p->d->sem_end);
	return (SUCCESS);
}

int	p_sleep(t_philo *p)
{
	if (print_status(p, SLEEP, now(p)) == 1)
		return (ERROR);
	usleep(p->d->ttslp);
	return (SUCCESS);
}

int	p_think(t_philo *p)
{
	if (print_status(p, THINK, now(p)) == 1)
		return (ERROR);
	usleep(p->d->ttthk);
	return (SUCCESS);
}

int	p_loop(t_philo *p)
{
	set_time_sem(p);
	while (1)
	{
		if (p->d->phqty < 2)
			continue ;
		sem_wait(p->d->sem_go);
		if (fork_take(p) == 0 && fork_take(p) == 0)
		{
			sem_post(p->d->sem_go);
			if (p_eat(p) == 1 || p_sleep(p) == 1 || p_think(p) == 1)
				endr(p);
		}
		else
			endr(p);
	}
	return (SUCCESS);
}
