/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:55 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 19:09:35 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 		Attribute forks to each philosofer
/// @param p	Pointer to the list of philosofers
/// @param f	Pointer to the list of forks
void	fork_set(t_philo *p, t_fork *f)
{
	t_philo	*tmp;

	tmp = p;
	while (tmp->next != NULL && tmp->next != p)
	{
		tmp->f[(tmp->id - 1) % 2] = &f[tmp->id - 1];
		tmp->f[tmp->id % 2] = &f[tmp->id];
		tmp = tmp->next;
	}
	if (p->info->phqty == 2)
	{
		tmp->f[0] = &f[0];
		tmp->f[1] = &f[1];
		return ;
	}
	tmp->f[0] = &f[tmp->id - 1];
	if (tmp->id > 1)
		tmp->f[1] = &f[0];
}

/// @brief 			Initializes the forks
/// @param p		Pointer to the list of philosofers
/// @param fork_id	fork to check status
/// @param philo_id	philo to check status
/// @return			SUCCESS if fork is free, ERROR otherwise
int	fork_check(t_philo *p, int fork_id, int philo_id)
{
	int	status;

	status = 0;
	if (pthread_mutex_lock(p->info->mtx_fcheck.mtx) == 0)
	{
		if (p->f[fork_id]->philo_id != philo_id)
			status = -1;
		if (pthread_mutex_unlock(p->info->mtx_fcheck.mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (mtx_fcheck)\n");
			return (ERROR);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (mtx_fcheck)\n");
		return (ERROR);
	}
	return (status);
}

/// @brief 			Updates the fork status
/// @param p		Pointer to the list of philosofers
/// @param fork_id	fork to update status
/// @param philo_id	philo to to update fork status
/// @return			SUCCESS if fork is free, ERROR otherwise
int	fork_upd(t_philo *p, int fork_id, int philo_id)
{
	if (pthread_mutex_lock(p->info->mtx_fcheck.mtx) == 0)
	{
		p->f[fork_id]->philo_id = philo_id;
		if (pthread_mutex_unlock(p->info->mtx_fcheck.mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (mtx_fcheck)\n");
			return (ERROR);
		}
	}
	else
	{
		printf("Error: pthread_mutex_lock (mtx_fcheck)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 			Drops the fork
/// @param p		Pointer to the list of philosofers
/// @param fork_id	fork to drop
/// @return			SUCCESS if fork is free, ERROR otherwise
int	fork_drop(t_philo *p, int fork_id)
{
	if (p->f[fork_id] == NULL)
		return (SUCCESS);
	if (fork_check(p, fork_id, p->id) == 0)
	{
		fork_upd(p, fork_id, 0);
		if (pthread_mutex_unlock(p->f[fork_id]->mtx) != 0)
		{
			printf("Error: pthread_mutex_unlock (fork)\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	fork_take(t_philo *p, int fork_id)
{
	struct timeval	t;
	int				status;

	status = 0;
	while (fork_check(p, fork_id, 0) != 0)
		status = check_died(p, &t);
	if (check_finished(p) == -1)
		return (status);
	if (pthread_mutex_lock(p->f[fork_id]->mtx) == 0)
	{
		fork_upd(p, fork_id, p->id);
		if (check_died(p, &t) == 1 || print_status(p, FORK, t) == 1)
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
