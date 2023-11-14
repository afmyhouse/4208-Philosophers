/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:04 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:07:06 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = check_died(p, &t);
	if (check_finished(p) == -1)
		return (status);
	if (status == 0)
	{
		p->t0 = t;
		print_status(p, EAT, t);
		usleep(ft_min(p->info->tteat, p->info->ttdie));
		if (p->info->eatqty != NULL && ++p->meals == *p->info->eatqty)
			set_finished(p, EAT);
	}
	if (fork_drop(p, 0) == 1 || fork_drop(p, 1) == 1)
		return (1);
	return (status);
}

int	p_sleep(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = check_died(p, &t);
	if (check_finished(p) == -1)
		return (status);
	if (status == 0)
	{
		if (print_status(p, SLEEP, t) == 1)
			return (1);
		if (p->info->ttslp + p->info->tteat < p->info->ttdie)
			usleep(p->info->ttslp);
		else
			usleep(p->info->ttdie - p->info->tteat);
	}
	return (check_died(p, &t));
}

int	p_think(t_philo *p)
{
	struct timeval	t;
	int				status;

	status = check_died(p, &t);
	if (check_finished(p) == -1)
		return (status);
	if (status == 1 || print_status(p, THINK, t) == 1)
		return (1);
	usleep(p->info->ttthk);
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo			*p;
	struct timeval	t;

	p = (t_philo *)philo;
	set_offset(philo);
	while (1)
	{
		if (check_died(philo, &t) == 1 || check_finished(p) == -1)
		{
			fork_drop(p, 0);
			fork_drop(p, 1);
			return (NULL);
		}
		if (p->f[1] == NULL || (fork_check(p, 0, 0) == 0 && p->go == 1))
			continue ;
		p->go = 0;
		if (!fork_take(philo, 0) && !fork_take(philo, 1))
		{
			if (p_eat(philo) == 1 || p_sleep(philo) == 1 || p_think(philo) == 1)
				return (NULL);
		}
		else
			return (NULL);
	}
	return (NULL);
}
