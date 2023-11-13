/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:19 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/13 19:06:24 by antoda-s         ###   ########.fr       */
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

/// @brief 		Initializes the t_info structure with global info
/// @param argv	Arguments with the info to initialize
/// @return		Pointer to the t_info structure
t_info	*init_info(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	ft_bzero(info, sizeof(t_info));
	info->phqty = ft_long_atoi(argv[1]);
	info->ttdie = ft_long_atoi(argv[2]);
	info->tteat = ft_long_atoi(argv[3]);
	info->ttslp = ft_long_atoi(argv[4]);
	if (argv[5] != NULL)
	{
		info->eatqty = malloc(sizeof(long long));
		*info->eatqty = ft_long_atoi(argv[5]);
	}
	if (invalid_info(info) == 1 && free_data(info) == 0)
		return (NULL);
	ft_msec2usec(&info->ttdie);
	ft_msec2usec(&info->tteat);
	ft_msec2usec(&info->ttslp);
	if (info->phqty % 2 && (info->ttdie - info->tteat - info->ttslp) / 2 > 0)
		info->ttthk = (info->ttdie - info->tteat - info->ttslp) / 2;
	return (info);
}

/// @brief 		Initializes the semaphores
/// @param info	Pointer to the t_info structure
/// @return		SUCCESS if semaphores are initialized, ERROR otherwise
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
