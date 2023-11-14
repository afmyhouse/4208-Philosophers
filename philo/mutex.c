/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:08 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:31:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 			Initializes the mutexes
/// @param info		Pointer to the info struct
/// @return			SUCCESS if all mutexes are initialized, ERROR otherwise
int	mtx_init(t_info *info)
{
	info->mtx_offset.mtx = malloc(sizeof(pthread_mutex_t));
	if (!info->mtx_offset.mtx
		|| pthread_mutex_init(info->mtx_offset.mtx, NULL) != 0)
		return (ERROR);
	info->mtx_print.mtx = malloc(sizeof(pthread_mutex_t));
	if (!info->mtx_print.mtx
		|| pthread_mutex_init(info->mtx_print.mtx, NULL) != 0)
		return (ERROR);
	info->mtx_death.mtx = malloc(sizeof(pthread_mutex_t));
	if (!info->mtx_death.mtx
		|| pthread_mutex_init(info->mtx_death.mtx, NULL) != 0)
		return (ERROR);
	info->mtx_fcheck.mtx = malloc(sizeof(pthread_mutex_t));
	if (!info->mtx_fcheck.mtx
		|| pthread_mutex_init(info->mtx_fcheck.mtx, NULL) != 0)
		return (ERROR);
	info->mtx_end.mtx = malloc(sizeof(pthread_mutex_t));
	if (!info->mtx_end.mtx
		|| pthread_mutex_init(info->mtx_end.mtx, NULL) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	mtx_destroy(pthread_mutex_t *mtx)
{
	if (pthread_mutex_destroy(mtx) != 0)
	{
		printf("Error: pthread_mutex_destroy\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	mtxs_destroyer(t_info *info, t_fork *f)
{
	int	i;

	i = 0;
	while (i++ < info->phqty)
	{
		if (mtx_destroy(f[i - 1].mtx) != 0)
			return (ERROR);
	}
	if (mtx_destroy(info->mtx_offset.mtx) != 0)
		return (ERROR);
	if (mtx_destroy(info->mtx_print.mtx) != 0)
		return (ERROR);
	if (mtx_destroy(info->mtx_death.mtx) != 0)
		return (ERROR);
	if (mtx_destroy(info->mtx_fcheck.mtx) != 0)
		return (ERROR);
	if (mtx_destroy(info->mtx_end.mtx) != 0)
		return (ERROR);
	return (SUCCESS);
}
