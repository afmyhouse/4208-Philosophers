/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:12 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 12:43:24 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_data(t_info *d)
{
	if (d->eatqty != NULL)
		free(d->eatqty);
	free(d);
	return (SUCCESS);
}

void	free_philo(t_philo *p)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = p;
	next = tmp;
	free_data(p->d);
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

int	sem_unlinker(void)
{
	if (sem_unlink("forks")
		|| sem_unlink("print")
		|| sem_unlink("death")
		|| sem_unlink("finish")
		|| sem_unlink("time")
		|| sem_unlink("go"))
	{
		printf("Error: sem_unlink (any unlink)\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	sem_closer(t_info *d)
{
	if (sem_close(d->sem_forks)
		|| sem_close(d->sem_print)
		|| sem_close(d->sem_death)
		|| sem_close(d->sem_end)
		|| sem_close(d->sem_time)
		|| sem_close(d->sem_go))
	{
		printf("Error: sem_close (any close)\n");
		return (ERROR);
	}
	return (sem_unlinker());
}
