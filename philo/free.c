/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:43:58 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 19:08:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_info *info)
{
	if (info->mealqty != NULL)
		free(info->mealqty);
	if (info->mtx_offset.mtx != NULL)
		free(info->mtx_offset.mtx);
	if (info->mtx_print.mtx != NULL)
		free(info->mtx_print.mtx);
	if (info->mtx_death.mtx != NULL)
		free(info->mtx_death.mtx);
	if (info->mtx_fcheck.mtx != NULL)
		free(info->mtx_fcheck.mtx);
	if (info->mtx_end.mtx != NULL)
		free(info->mtx_end.mtx);
	free(info);
	return (SUCCESS);
}

void	free_fork(t_fork *f, int n_philo)
{
	int		i;

	i = 0;
	if (f != NULL)
	{
		while (i++ < n_philo)
		{
			if (f[i - 1].mtx != NULL)
				free(f[i - 1].mtx);
		}
		free(f);
	}
}

void	free_philo(t_philo *p, t_fork *f)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = p;
	next = tmp;
	free_fork(f, p->info->phqty);
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
