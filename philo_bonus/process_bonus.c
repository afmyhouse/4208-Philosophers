/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:01:56 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 23:02:24 by antoda-s         ###   ########.fr       */
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
	i = p->info->phqty;
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

	if (get_time(&p->info->tstart) == -1)
		return (ERROR);
	i = p->info->phqty;
	tmp = p;
	while (i--)
	{
		tmp->t0 = p->info->tstart;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/// @brief 		Fetchs current time to philo timer
/// @param p	Pointer to the philosofer structure
/// @return		SUCCESS if philo is dead, 0 otherwise
int	set_time_sem(t_philo *p)
{
	if (sem_wait(p->info->sem_time) == 0)
	{
		if (get_time(&p->tnow) == -1)
			return (ERROR);
		if (sem_post(p->info->sem_time) != 0)
		{
			printf("Error: sem_post (time)\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}
