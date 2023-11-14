/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:01:56 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 18:45:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief 		Creates the processes
/// @param p	Pointer to the list of philosofers
/// @return		SUCCESS if processes were created, ERROR otherwise
int	set_processes(t_philo *p)
{
	t_philo		*tmp;
	int			i;
	pthread_t	thread;

	tmp = p;
	i = p->d->phqty;
	set_time_start(p);
	while (i--)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (ERROR);
		else if (tmp->pid == 0)
		{
			if (pthread_create(&thread, NULL, &lifeguard, tmp) != 0)
				return (ERROR);
			if (pthread_detach(thread) != 0)
				return (ERROR);
			exit(p_loop(tmp));
		}
		else
			tmp = tmp->next;
	}
	return (SUCCESS);
}

/// @brief 		set the tstart time
/// @param p	Pointer to the list of philosofers
/// @return		SUCCESS if tstart was set, ERROR otherwise
int	set_time_start(t_philo *p)
{
	int		i;
	t_philo	*tmp;

	if (set_time(&p->d->tstart) == -1)
		return (ERROR);
	i = p->d->phqty;
	tmp = p;
	while (i--)
	{
		tmp->t0 = p->d->tstart;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/// @brief 		Checks if the philo is dead
/// @param p	Pointer to the philosofer
/// @return		SUCCESS if philo is dead, 0 otherwise
int	set_time_sem(t_philo *p)
{
	if (sem_wait(p->d->sem_time) == 0)
	{
		if (set_time(&p->t) == -1)
			return (ERROR);
		if (sem_post(p->d->sem_time) != 0)
		{
			printf("Error: sem_post (time)\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}