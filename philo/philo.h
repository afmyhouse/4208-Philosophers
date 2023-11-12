/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:42 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 22:26:18 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
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

typedef struct s_fork
{
	int				id;
	int				philo_id;
	pthread_mutex_t	*mtx;
}	t_fork;

typedef struct s_info
{
	int				phqty;
	long long		ttdie;
	long long		tteat;
	long long		ttslp;
	long long		ttthk;
	long long		*mealqty;
	struct timeval	offset;
	long long		end;
	t_fork			mtx_offset;
	t_fork			mtx_print;
	t_fork			mtx_death;
	t_fork			mtx_fcheck;
	t_fork			mtx_end;
}	t_info;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	t_fork				*f[2];
	t_info				*info;
	struct timeval		t0;
	int					meals;
	int					go;
	struct s_philo		*prev;
	struct s_philo		*next;
}	t_philo;

int			invalid_info(t_info *d);
//static int	invalid_argc(int argc);
//static int	invalid_argv(char **argv);
//static int	invalid_argv(char **argv)

int			mtx_init(t_info *d);
int			set_time(struct timeval *t);
long long	utimestamp(struct timeval t0);
long long	utime(struct timeval t);
long long	dtime(struct timeval t0, struct timeval t1);

t_info		*info_init(char **argv);
t_philo		*philo_new(int id, t_info *data);
void		philo_add(t_philo **p, t_philo *new);
t_philo		*philo_init(t_info *data);

int			set_threads(t_philo *p);

t_fork		*fork_init(t_philo *p);
int			mtx_destroy(pthread_mutex_t *mtx);
int			mtxs_destroyer(t_info *d, t_fork *f);

int			fork_take(t_philo *p, int fork_id);
int			p_eat(t_philo *p);
int			p_sleep(t_philo *p);
int			p_think(t_philo *p);
void		*philo_loop(void *philo);

int			set_offset(t_philo *p);
int			set_finished(t_philo *p, int state);
int			check_finished(t_philo *p);
int			check_died(t_philo *p, struct timeval *t);
int			status_print(t_philo *p, int state, struct timeval t);

void		fork_set(t_philo *p, t_fork *f);
int			fork_check(t_philo *p, int fork_id, int philo_id);
int			fork_upd(t_philo *p, int fork_id, int philo_id);
int			fork_drop(t_philo *p, int fork_id);
int			join_threads(t_philo *p);

int			free_data(t_info *d);
void		free_fork(t_fork *f, int n_philo);
void		free_philo(t_philo *p, t_fork *f);

size_t		ft_strlen(const char *s);
long long	ft_long_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
long long	ft_min(long long a, long long b);
void		ft_msec2usec(void *t);

#endif
