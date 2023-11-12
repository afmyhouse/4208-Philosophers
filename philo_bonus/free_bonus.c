/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:53:18 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:13:26 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_data(t_info *d)
{
	if (d->cap != NULL)
		free(d->cap);
	free(d);
	return (0);
}

void	philofree(t_philo *p)
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

int	semunlinker(void)
{
	if (sem_unlink("forks") != 0 || sem_unlink("print") != 0)
	{
		printf("Error: sem_unlink (forks)\n");
		return (1);
	}
	if (sem_unlink("death") != 0 || sem_unlink("end") != 0)
	{
		printf("Error: sem_unlink (death)\n");
		return (1);
	}
	if (sem_unlink("time") != 0 || sem_unlink("go") != 0)
	{
		printf("Error: sem_unlink (time)\n");
		return (1);
	}
	return (0);
}

int	semdestroyer(t_info *d)
{
	if (sem_close(d->sem_forks) != 0 || sem_close(d->sem_print) != 0)
	{
		printf("Error: sem_close (forks)\n");
		return (1);
	}
	if (sem_close(d->sem_death) != 0 || sem_close(d->sem_end) != 0)
	{
		printf("Error: sem_close (death)\n");
		return (1);
	}
	if (sem_close(d->sem_time) != 0 || sem_close(d->sem_go) != 0)
	{
		printf("Error: sem_close (time)\n");
		return (1);
	}
	if (semunlinker() == 1)
		return (1);
	return (0);
}
