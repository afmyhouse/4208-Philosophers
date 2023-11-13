/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:48:08 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 11:02:32 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 		Set threads to start looping
/// @param p	Pointer to the list of philosofers
/// @return		SUCCESS if threads are set, ERROR otherwise
int	set_threads(t_philo *p)
{
	t_philo	*tmp;

	tmp = p;
	while (tmp->next != NULL && tmp->next != p)
	{
		if (pthread_create(&tmp->thread, NULL, philo_loop, (void *)tmp) != 0)
		{
			printf("Error: pthread_create\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	if (pthread_create(&tmp->thread, NULL, philo_loop, (void *)tmp) != 0)
	{
		printf("Error: pthread_create\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Join threads
/// @param p	Pointer to the list of philosofers
/// @return		SUCCESS if threads are joined, ERROR otherwise
int	join_threads(t_philo *p)
{
	t_philo	*tmp;

	tmp = p;
	while (tmp->next != NULL && tmp->next != p)
	{
		if (pthread_join(tmp->thread, NULL) != 0)
		{
			printf("Error: pthread_join\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	if (pthread_join(tmp->thread, NULL) != 0)
	{
		printf("Error: pthread_join\n");
		return (ERROR);
	}
	return (SUCCESS);
}
