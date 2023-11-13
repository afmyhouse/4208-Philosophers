/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:19 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 18:02:30 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief 		Creates a new philosofer and initializes it
/// @param id	Philosofer's id
/// @param info	Pointer to the t_info structure
/// @return		Pointer to the new philosofer
t_philo	*new_philo(int id, t_info *info)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	ft_bzero(p, sizeof(t_philo));
	p->id = id;
	p->d = info;
	return (p);
}

/// @brief 		Adds a new created philosofer to the list
/// @param p	Pointer to the list of philosofers
/// @param		new	Pointer to the new philosofer
void	add_philo(t_philo **p, t_philo *new)
{
	t_philo	*tmp;

	if (!*p)
	{
		*p = new;
		return ;
	}
	tmp = *p;
	while (tmp->id != new->id - 1)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = *p;
	(*p)->prev = new;
}

/// @brief		Initializes the philosofer's list
/// @param info	Pointer to the t_info structure
/// @return		Pointer to the list of philosofers
t_philo	*init_philo(t_info *info)
{
	int		i;
	t_philo	*p;
	t_philo	*new;

	p = NULL;
	new = NULL;
	i = 0;
	while (++i <= info->phqty)
	{
		new = new_philo(i, info);
		if (!new)
		{
			free_philo(p);
			free_data(info);
			return (NULL);
		}
		add_philo(&p, new);
	}
	return (p);
}


int	init_semaphore(t_info *info)
{
	sem_unlink("forks");
	info->sem_forks = sem_open("forks", O_CREAT, 0644, info->phqty);
	if (info->sem_forks == SEM_FAILED)
		return (ERROR);
	sem_unlink("print");
	info->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (info->sem_print == SEM_FAILED)
		return (ERROR);
	sem_unlink("death");
	info->sem_death = sem_open("death", O_CREAT, 0644, 1);
	if (info->sem_death == SEM_FAILED)
		return (ERROR);
	sem_unlink("go");
	info->sem_go = sem_open("go", O_CREAT, 0644, info->phqty / 2);
	if (info->sem_go == SEM_FAILED)
		return (ERROR);
	sem_unlink("end");
	info->sem_end = sem_open("end", O_CREAT, 0644, 0);
	if (info->sem_end == SEM_FAILED)
		return (ERROR);
	sem_unlink("time");
	info->sem_time = sem_open("time", O_CREAT, 0644, 1);
	if (info->sem_time == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}
