/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:46 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 22:55:59 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	p_eat(t_philo *p)
{
	if (sem_wait(p->info->sem_death) == 0)
	{
		p->t0 = now(p);
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
	print_status(p, EAT, now(p));
	usleep(ft_min(p->info->tteat, p->info->ttdie));
	if (fork_drop(p) == 1 || fork_drop(p) == 1)
		return (ERROR);
	if (p->info->eatqty != NULL && ++p->meals == *p->info->eatqty)
		sem_post(p->info->sem_end);
	return (SUCCESS);
}

int	p_sleep(t_philo *p)
{
	if (print_status(p, SLEEP, now(p)) == 1)
		return (ERROR);
	usleep(p->info->ttslp);
	return (SUCCESS);
}

int	p_think(t_philo *p)
{
	if (print_status(p, THINK, now(p)) == 1)
		return (ERROR);
	usleep(p->info->ttthk);
	return (SUCCESS);
}

/// @brief 		Finish loop of the philosofer
/// @param p	Pointer to the philosofer
/// @return		ERROR if any error occurs, SUCCESS otherwise
void	p_finish(t_philo *p)
{
	int	i;

	i = p->info->phqty;
	while (i--)
	{
		if (sem_post(p->info->sem_end) != 0)
		{
			printf("Error: sem_post (sem_end)\n");
			exit(ERROR);
		}
	}
}

/// @brief 		Loop of the philosofer
/// @param p	Pointer to the philosofer
/// @return		SUCCESS if philo is dead, 0 otherwise
int	p_loop(t_philo *p)
{
	set_time_sem(p);
	while (1)
	{
		if (p->info->phqty < 2)
			continue ;
		sem_wait(p->info->sem_start);
		if (fork_take(p) == 0 && fork_take(p) == 0)
		{
			sem_post(p->info->sem_start);
			if (p_eat(p) == 1 || p_sleep(p) == 1 || p_think(p) == 1)
				p_finish(p);
		}
		else
			p_finish(p);
	}
	return (SUCCESS);
}
