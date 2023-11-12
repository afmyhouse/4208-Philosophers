/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:08 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:39:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_aux_mtx(t_info *d)
{
	d->mtx_offset.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_offset.mtx || pthread_mutex_init(d->mtx_offset.mtx, NULL) != 0)
		return (ERROR);
	d->mtx_print.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_print.mtx || pthread_mutex_init(d->mtx_print.mtx, NULL) != 0)
		return (ERROR);
	d->mtx_death.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_death.mtx || pthread_mutex_init(d->mtx_death.mtx, NULL) != 0)
		return (ERROR);
	d->mtx_fcheck.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_fcheck.mtx || pthread_mutex_init(d->mtx_fcheck.mtx, NULL) != 0)
		return (ERROR);
	d->mtx_end.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_end.mtx || pthread_mutex_init(d->mtx_end.mtx, NULL) != 0)
		return (ERROR);
	return (SUCCESS);
}

t_fork	*forkinit(t_philo *p)
{
	t_fork	*f;
	int		i;

	f = malloc(sizeof(t_fork) * p->d->phqty);
	if (!f)
		return (NULL);
	ft_bzero(f, sizeof(t_fork) * p->d->phqty);
	i = 0;
	while (++i <= p->d->phqty)
	{
		f[i - 1].mtx = malloc(sizeof(pthread_mutex_t));
		if (!f[i - 1].mtx)
		{
			philo_free(p, f);
			return (NULL);
		}
		if (pthread_mutex_init(f[i - 1].mtx, NULL) != 0)
		{
			printf("Error: pthread_mutex_init\n");
			philo_free(p, f);
			return (NULL);
		}
		f[i - 1].id = i;
	}
	return (f);
}

int	mtxdestroy(pthread_mutex_t *mtx)
{
	if (pthread_mutex_destroy(mtx) != 0)
	{
		printf("Error: pthread_mutex_destroy\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	destroyer(t_info *d, t_fork *f)
{
	int	i;

	i = 0;
	while (i++ < d->phqty)
	{
		if (mtxdestroy(f[i - 1].mtx) != 0)
			return (ERROR);
	}
	if (mtxdestroy(d->mtx_offset.mtx) != 0)
		return (ERROR);
	if (mtxdestroy(d->mtx_print.mtx) != 0)
		return (ERROR);
	if (mtxdestroy(d->mtx_death.mtx) != 0)
		return (ERROR);
	if (mtxdestroy(d->mtx_fcheck.mtx) != 0)
		return (ERROR);
	if (mtxdestroy(d->mtx_end.mtx) != 0)
		return (ERROR);
	return (SUCCESS);
}
