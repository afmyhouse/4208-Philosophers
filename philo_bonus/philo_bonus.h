/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:04 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 12:35:07 by antoda-s         ###   ########.fr       */
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
	struct timeval	offset;
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
	t_info				*d;
	struct timeval		t0;
	struct timeval		t;
	int					meals;
	struct s_philo		*prev;
	struct s_philo		*next;
}	t_philo;

//static int	argccheck(int argc);
//static int	inputcheck(char **argv);
int	invalid_info(t_info *d);

int				set_time(t_philo *p);
struct timeval	now(t_philo *p);
long long		utime(struct timeval t);
long long		dtime(struct timeval t0, struct timeval t1);

t_info			*init_info(char **argv);
t_philo			*new_philo(int id, t_info *data);
void			add_philo(t_philo **p, t_philo *new);
t_philo			*init_philo(t_info *data);

int				set_processes(t_philo *p);
int				init_semaphore(t_info *data);

int				fork_take(t_philo *p);
int				p_eat(t_philo *p);
int				p_sleep(t_philo *p);
int				p_think(t_philo *p);
int				philo_loop(t_philo *p);

int				set_offset(t_philo *p);
int				check_died(t_philo *p);
int				print_status(t_philo *p, int state, struct timeval t);
void			*lifeguard(void *philo);

int				fork_drop(t_philo *p);
void			endr(t_philo *p);
int				philo_service(t_philo *p);

int				sem_unlinker(void);
int				sem_closer(t_info *d);
int				free_data(t_info *d);
void			free_philo(t_philo *p);

size_t			ft_strlen(const char *s);
long long		ft_long_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
long long		ft_min(long long a, long long b);
void			ft_msec2usec(void *t);

#endif