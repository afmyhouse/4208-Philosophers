/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:13 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/10 12:42:41 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*p;
	t_fork	*f;
	t_data	*d;

	if (valid_argc(argc) == 1 || valid_argv(argv) == ERROR)
		return (ERROR);
	d = get_data(argv);
	if (!d)
		return (ERROR);
	if (set_aux_mutexes(d) == 1 && datafree(d) == 0)
		return (ERROR);
	p = philo_init(d);
	if (!p)
		return (ERROR);
	f = forkinit(p);
	if (!f)
		return (ERROR);
	set_forks(p, f);
	if (set_threads(p) == 1 || join_threads(p) == 1 || destroyer(d, f) == 1)
	{
		philofree(p, f);
		return (1);
	}
	philofree(p, f);
	return (0);
}
