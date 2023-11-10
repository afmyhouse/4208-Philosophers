/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:08 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/09 15:20:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_aux_mutexes(t_data *d)
{
	d->mtx_offset.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_offset.mtx || pthread_mutex_init(d->mtx_offset.mtx, NULL) != 0)
		return (1);
	d->mtx_print.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_print.mtx || pthread_mutex_init(d->mtx_print.mtx, NULL) != 0)
		return (1);
	d->mtx_death.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_death.mtx || pthread_mutex_init(d->mtx_death.mtx, NULL) != 0)
		return (1);
	d->mtx_fcheck.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_fcheck.mtx || pthread_mutex_init(d->mtx_fcheck.mtx, NULL) != 0)
		return (1);
	d->mtx_end.mtx = malloc(sizeof(pthread_mutex_t));
	if (!d->mtx_end.mtx || pthread_mutex_init(d->mtx_end.mtx, NULL) != 0)
		return (1);
	return (0);
}

t_fork	*forkinit(t_philo *p)
{
	t_fork	*f;
	int		i;

	f = malloc(sizeof(t_fork) * p->d->qty);
	if (!f)
		return (NULL);
	ft_bzero(f, sizeof(t_fork) * p->d->qty);
	i = 0;
	while (++i <= p->d->qty)
	{
		f[i - 1].mtx = malloc(sizeof(pthread_mutex_t));
		if (!f[i - 1].mtx)
		{
			philofree(p, f);
			return (NULL);
		}
		if (pthread_mutex_init(f[i - 1].mtx, NULL) != 0)
		{
			printf("Error: pthread_mutex_init\n");
			philofree(p, f);
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
		return (1);
	}
	return (0);
}

int	destroyer(t_data *d, t_fork *f)
{
	int	i;

	i = 0;
	while (i++ < d->qty)
	{
		if (mtxdestroy(f[i - 1].mtx) != 0)
			return (1);
	}
	if (mtxdestroy(d->mtx_offset.mtx) != 0)
		return (1);
	if (mtxdestroy(d->mtx_print.mtx) != 0)
		return (1);
	if (mtxdestroy(d->mtx_death.mtx) != 0)
		return (1);
	if (mtxdestroy(d->mtx_fcheck.mtx) != 0)
		return (1);
	if (mtxdestroy(d->mtx_end.mtx) != 0)
		return (1);
	return (0);
}
