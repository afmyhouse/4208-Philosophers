/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:01:56 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:02:51 by antoda-s         ###   ########.fr       */
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
	set_offset(p);
	while (i--)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (ERROR);
		else if (tmp->pid == 0)
		{
			if (pthread_create(&thread, NULL, &bigbrother, tmp) != 0)
				return (ERROR);
			if (pthread_detach(thread) != 0)
				return (ERROR);
			exit(philo_routine(tmp));
		}
		else
			tmp = tmp->next;
	}
	return (SUCCESS);
}
