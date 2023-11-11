/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:13 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/11 14:39:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 			checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if number of arguments is valid, ERROR otherwise
int	invalid_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 			checks if the arguments are valid
/// @param argv		arguments to validate
/// @return			SUCCESS if arguments are valid, ERROR otherwise
int	invalid_argv(char **argv)
{
	int		i;
	char	*t;
	int		sign;

	i = 0;
	while (argv[++i])
	{
		t = argv[i];
		sign = 1;
		while (*t)
		{
			if (((*t == '-' || *t == '+') && sign) || (*t >= '0' && *t <= '9'))
			{
				sign = 0;
				t++;
			}
			else
			{
				printf("Error: invalid arguments\n");
				return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

static int	init_all(char **argv)
{
	t_philo	*p;
	t_fork	*f;
	t_info	*info;

	info = philo_info(argv);
	if (!info)
		return (ERROR);
	if (init_aux_mtx(info) == ERROR && free_data(info) == SUCCESS)
		return (ERROR);
	p = philo_init(info);
	if (!p)
		return (ERROR);
	f = forkinit(p);
	if (!f)
		return (ERROR);
	set_forks(p, f);
	if (set_threads(p) == 1 || join_threads(p) == 1 || destroyer(info, f) == 1)
	{
		philo_free(p, f);
		return (ERROR);
	}
	philo_free(p, f);
	return (SUCCESS);
}

/// @brief 			Main checks arguments are valid and initializes the program
/// @param argc		Number of arguments
/// @param argv		Arguments to validate
/// @return			SUCCESS if program ran successfully, ERROR otherwise
int	main(int argc, char **argv)
{
	if (invalid_argc(argc) || invalid_argv(argv))
		return (ERROR);
	init_all(argv);
	return (SUCCESS);
}
