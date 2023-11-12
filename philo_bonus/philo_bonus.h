/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:53:22 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:42:22 by antoda-s         ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define INTMAX	2147483647
# define INTMIN	-2147483648

typedef struct s_info
{
	int				phqty;
	long long		ttdie;
	long long		tteat;
	long long		ttslp;
	long long		ttthk;
	long long		*cap;
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
	t_info				*info;
	struct timeval		t0;
	struct timeval		t;
	int					meals;
	struct s_philo		*prev;
	struct s_philo		*next;
}	t_philo;

int				invalid_argc(int argc);
int				invalid_argv(char **argv);
int				invalid_info(t_info *d);
t_info			*info_init(char **argv);

int				set_time(t_philo *p);
struct timeval	now(t_philo *p);
long long		utime(struct timeval t);
long long		deltatime(struct timeval t0, struct timeval t1);

t_philo			*philo_new(int id, t_info *data);
void			philo_add(t_philo **p, t_philo *new);
t_philo			*philo_init(t_info *data);
int				set_processes(t_philo *p);
int				seminit(t_info *data);

int				grab_fork(t_philo *p);
int				eat(t_philo *p);
int				nap(t_philo *p);
int				think(t_philo *p);
int				philo_routine(t_philo *p);

int				set_offset(t_philo *p);
int				deathcheck(t_philo *p);
int				printstate(t_philo *p, int state, struct timeval t);
void			*bigbrother(void *philo);

int				fork_drop(t_philo *p);
void			endr(t_philo *p);
int				philo_waiter(t_philo *p);

int				semunlinker(void);
int				semdestroyer(t_info *d);
int				free_data(t_info *d);
void			philofree(t_philo *p);

size_t			ft_strlen(const char *s);
long long		ft_long_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
long long		ft_min(long long a, long long b);

#endif