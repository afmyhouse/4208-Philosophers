/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:13 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 15:24:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 		Check validity the TTDIE, TTEAT, TTSLP, PHQTY parameters
/// @param info	Pointer to the t_info structure
/// @return		SUCCESS if parameters are valid, ERROR otherwise
int	invalid_info(t_info *info)
{
	if (info->phqty < 1 || info->phqty > INTMAX
		|| info->ttdie < 0 || info->ttdie > INTMAX || info->ttdie < INTMIN
		|| info->tteat < 0 || info->tteat > INTMAX || info->tteat < INTMIN
		|| info->ttslp < 0 || info->ttslp > INTMAX || info->ttslp < INTMIN
		|| (info->eatqty != NULL
			&& (*info->eatqty < 1 || *info->eatqty > INTMAX
				|| *info->eatqty < INTMIN)))
	{
		printf("Error: invalid arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 			checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if number of arguments is valid, ERROR otherwise
static int	invalid_argc(int argc)
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
static int	invalid_argv(char **argv)
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

/// @brief 		Initializes all variables ant starts the program
/// @param argv	Arguments with the info to initialize
/// @return		SUCCESS if program ran successfully, ERROR otherwise
static int	init_all(char **argv)
{
	t_philo	*p;
	t_fork	*f;
	t_info	*info;

	info = init_info(argv);
	if (!info)
		return (ERROR);
	if (mtx_init(info) == ERROR && free_data(info) == SUCCESS)
		return (ERROR);
	p = init_philo(info);
	if (!p)
		return (ERROR);
	f = init_fork(p);
	if (!f)
		return (ERROR);
	fork_set(p, f);
	if (set_threads(p) == 1
		|| join_threads(p) == 1
		|| mtxs_destroyer(info, f) == 1)
	{
		free_philo(p, f);
		return (ERROR);
	}
	free_philo(p, f);
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
	return (init_all(argv));
}
