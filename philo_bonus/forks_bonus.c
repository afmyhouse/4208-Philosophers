/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:14:12 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 18:49:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief 			Drops the fork
/// @param p		Pointer to the list of philosofers
/// @return			SUCCESS if fork is free, ERROR otherwise
int	fork_drop(t_philo *p)
{
	if (sem_post(p->info->sem_forks) != 0)
	{
		printf("Error: sem_post (fork)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Takes the fork
/// @param p	Pointer to the philosofer
/// @return		SUCCESS if fork is taken, ERROR otherwise
int	fork_take(t_philo *p)
{
	if (sem_wait(p->info->sem_forks) == 0)
	{
		if (print_status(p, FORK, now(p)) == 1)
			return (ERROR);
	}
	else
	{
		printf("Error: sem_wait (forks)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Checks if the meal is over
/// @param p	Pointer to the philosofer
void	endr(t_philo *p)
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
