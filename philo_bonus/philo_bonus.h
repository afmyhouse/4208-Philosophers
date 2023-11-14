/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:04 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 18:49:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "error.h"

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define INTMAX	2147483647
# define INTMIN	-2147483648
# define PHQTY 1
# define TTDIE 2
# define TTEAT 3
# define TTSLP 4
# define MEALQTY 5

typedef struct s_info
{
	int				phqty;
	long long		ttdie;
	long long		tteat;
	long long		ttslp;
	long long		ttthk;
	long long		*eatqty;
	struct timeval	tstart;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_death;
	sem_t			*sem_go;
	sem_t			*sem_end;
	sem_t			*sem_time;
}	t_info;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	t_info				*info;
	struct timeval		t0;
	struct timeval		t;
	int					meals;
	struct s_philo		*prev;
	struct s_philo		*next;
}	t_philo;

/// main_bonus.c index
int				invalid_info(t_info *d);
//static int	invalid_argc(int argc)
//static int	invalid_argv(char **argv)
//static int	init_all(char **argv)
//int	main(int argc, char **argv)

/// forks_bonus.c index
int				fork_drop(t_philo *p);
int				fork_take(t_philo *p);
void			endr(t_philo *p);

/// free_bonus.c index
int				free_data(t_info *info);
void			free_philo(t_philo *p);
int				sem_unlinker(void);
int				sems_destroyer(t_info *d);

/// ft_tools.c index
size_t			ft_strlen(const char *s);
long long		ft_long_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
long long		ft_min(long long a, long long b);

/// init_bonus.c index
t_philo			*new_philo(int id, t_info *info);
void			add_philo(t_philo **p, t_philo *new);
t_philo			*init_philo(t_info *info);
t_info			*init_info(char **argv);
int				init_semaphore(t_info *info);

/// lifeguard_bonus.c index
int				check_died(t_philo *p);
int				print_status(t_philo *p, int state, struct timeval t);
void			*lifeguard(void *philo);
int				philo_service(t_philo *p);

/// loop_bonus.c index
int				p_eat(t_philo *p);
int				p_sleep(t_philo *p);
int				p_think(t_philo *p);
int				p_loop(t_philo *p);

/// process_bonus.c index
int				set_processes(t_philo *p);
int				set_time_start(t_philo *p);
int				set_time_sem(t_philo *p);

/// time_bonus.c index
int				set_time(struct timeval *t);
struct timeval	now(t_philo *p);
long long		utime(struct timeval t);
long long		dtime(struct timeval t0, struct timeval t1);
void			ft_msec2usec(void *t);

#endif