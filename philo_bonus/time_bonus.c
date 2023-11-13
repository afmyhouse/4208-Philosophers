/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:52 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:05:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_time(t_philo *p)
{
	if (sem_wait(p->d->sem_time) == 0)
	{
		if (gettimeofday(&p->t, NULL) == -1)
		{
			printf("Error: gettimeofday\n");
			return (1);
		}
		if (sem_post(p->d->sem_time) != 0)
			printf("Error: sem_post (time)\n");
	}
	return (SUCCESS);
}

struct timeval	now(t_philo *p)
{
	struct timeval	now;

	ft_bzero(&now, sizeof(struct timeval));
	if (sem_wait(p->d->sem_time) == 0)
	{
		now = p->t;
		if (sem_post(p->d->sem_time) != 0)
			printf("Error: sem_post (time)\n");
	}
	return (now);
}

long long	utime(struct timeval t)
{
	return (t.tv_sec * 1000000 + t.tv_usec);
}

long long	dtime(struct timeval t0, struct timeval t1)
{
	return ((utime(t1) - utime(t0)) / 1000);
}

void	ft_msec2usec(void *t)
{
	*(long long *)t = *(long long *)t * 1000;
}
