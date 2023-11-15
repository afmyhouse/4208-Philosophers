/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:12 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 22:46:58 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief		Free the t_info structure
/// @param info	Pointer to the t_info structure
/// @return		SUCCESS if free is successful, ERROR otherwise
int	free_data(t_info *info)
{
	if (info->eatqty != NULL)
		free(info->eatqty);
	free(info);
	return (SUCCESS);
}

/// @brief 		Free the t_philo structure
/// @param p	Pointer to the t_philo structure
void	free_philo(t_philo *p)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = p;
	next = tmp;
	free_data(p->info);
	if (p != NULL)
	{
		while (tmp->next != NULL && tmp->next != p)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		free(tmp);
	}
}

/// @brief 		Unlink semaphorese
/// @param		none
/// @return		SUCCESS if unlink is successful, ERROR otherwise
int	sem_unlinker(void)
{
	if (sem_unlink("forks")
		|| sem_unlink("print")
		|| sem_unlink("death")
		|| sem_unlink("finish")
		|| sem_unlink("time")
		|| sem_unlink("start"))
	{
		printf("Error: sem_unlink (any unlink)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Destroy semaphores
/// @param info	Pointer to the t_info structure
/// @return		SUCCESS if destroy is successful, ERROR otherwise
int	sems_destroyer(t_info *info)
{
	if (sem_close(info->sem_forks)
		|| sem_close(info->sem_print)
		|| sem_close(info->sem_death)
		|| sem_close(info->sem_end)
		|| sem_close(info->sem_time)
		|| sem_close(info->sem_start))
	{
		printf("Error: sem_close (any close)\n");
		return (ERROR);
	}
	return (sem_unlinker());
}
