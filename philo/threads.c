/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:48:08 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:37:21 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_threads(t_philo *p)
{
	t_philo	*tmp;

	tmp = p;
	while (tmp->next != NULL && tmp->next != p)
	{
		if (pthread_create(&tmp->thread, NULL, philo_routine, (void *)tmp) != 0)
		{
			printf("Error: pthread_create\n");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	if (pthread_create(&tmp->thread, NULL, philo_routine, (void *)tmp) != 0)
	{
		printf("Error: pthread_create\n");
		return (ERROR);
	}
	return (SUCCESS);
}

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
