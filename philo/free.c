/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:43:58 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:39:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_info *d)
{
	if (d->cap != NULL)
		free(d->cap);
	if (d->mtx_offset.mtx != NULL)
		free(d->mtx_offset.mtx);
	if (d->mtx_print.mtx != NULL)
		free(d->mtx_print.mtx);
	if (d->mtx_death.mtx != NULL)
		free(d->mtx_death.mtx);
	if (d->mtx_fcheck.mtx != NULL)
		free(d->mtx_fcheck.mtx);
	if (d->mtx_end.mtx != NULL)
		free(d->mtx_end.mtx);
	free(d);
	return (SUCCESS);
}

void	forkfree(t_fork *f, int n_philo)
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

void	philo_free(t_philo *p, t_fork *f)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = p;
	next = tmp;
	forkfree(f, p->d->phqty);
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
