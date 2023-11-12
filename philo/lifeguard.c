/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeguard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:43:54 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 19:08:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_offset(t_philo *p)
{
	if (pthread_mutex_lock(p->info->mtx_offset.mtx) == 0)
	{
		if (p->info->offset.tv_sec == 0)
			set_time(&p->info->offset);
		p->t0 = p->info->offset;
		if (pthread_mutex_unlock(p->info->mtx_offset.mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (mtx_offset)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (mtx_offset)\n");
		return (1);
	}
	return (0);
}

int	endset(t_philo *p, int state)
{
	if (pthread_mutex_lock(p->info->mtx_end.mtx) == 0)
	{
		if (state == DEAD)
			p->info->end = 1;
		if (p->info->mealqty != NULL && state == EAT)
			p->info->end++;
		if (pthread_mutex_unlock(p->info->mtx_end.mtx) != 0)
		{
			printf("Error: mutex unlock (mtx_end)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: mutex lock (mtx_end)\n");
		return (1);
	}
	return (0);
}

int	endcheck(t_philo *p)
{
	int	status;

	status = 0;
	if (pthread_mutex_lock(p->info->mtx_end.mtx) == 0)
	{
		if (p->info->end >= 1)
			status = -1;
		if (pthread_mutex_unlock(p->info->mtx_end.mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (mtx_end)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (mtx_end)\n");
		return (1);
	}
	return (status);
}

int	deathcheck(t_philo *p, struct timeval *t)
{
	if (pthread_mutex_lock(p->info->mtx_death.mtx) == 0)
	{
		if (set_time(t) == 0)
		{
			if (utime(*t) - utime(p->t0) > p->info->ttdie)
			{
				printstate(p, 4, *t);
				endset(p, DEAD);
			}
		}
		if (pthread_mutex_unlock(p->info->mtx_death.mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (mtx_death)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (mtx_death)\n");
		return (1);
	}
	return (0);
}

int	printstate(t_philo *p, int state, struct timeval t)
{
	if (pthread_mutex_lock(p->info->mtx_print.mtx) == 0)
	{
		if (endcheck(p) == -1)
		{
			pthread_mutex_unlock(p->info->mtx_print.mtx);
			return (0);
		}
		if (state == FORK)
			printf("%lld %d has taken a fork\n", \
				deltatime(p->info->offset, t), p->id);
		else if (state == EAT)
			printf("%lld %d is eating\n", deltatime(p->info->offset, t), p->id);
		else if (state == SLEEP)
			printf("%lld %d is sleeping\n", deltatime(p->info->offset, t), p->id);
		else if (state == THINK)
			printf("%lld %d is thinking\n", deltatime(p->info->offset, t), p->id);
		else if (state == DEAD)
			printf("%lld %d died\n", deltatime(p->info->offset, t), p->id);
		if (pthread_mutex_unlock(p->info->mtx_print.mtx) != 0)
		{
			printf("Error: mutex unlock (mtx_print)\n");
			return (1);
		}
	}
	return (0);
}
