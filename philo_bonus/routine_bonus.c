
#include "philo_bonus.h"

int	grab_fork(t_philo *p)
{
	if (sem_wait(p->info->sem_forks) == 0)
	{
		if (printstate(p, FORK, now(p)) == 1)
			return (1);
	}
	else
	{
		printf("Error: sem_wait (forks)\n");
		return (1);
	}
	return (0);
}

int	eat(t_philo *p)
{
	if (sem_wait(p->info->sem_death) == 0)
	{
		p->t0 = now(p);
		if (sem_post(p->info->sem_death) != 0)
		{
			printf("Error: sem_post (sem_death)\n");
			return (1);
		}
	}
	else
	{
		printf("Error: sem_wait (sem_death)\n");
		return (1);
	}
	printstate(p, EAT, now(p));
	usleep(ft_min(p->info->tteat, p->info->ttdie));
	if (fork_drop(p) == 1 || fork_drop(p) == 1)
		return (1);
	if (p->info->cap != NULL && ++p->meals == *p->info->cap)
		sem_post(p->info->sem_end);
	return (0);
}

int	nap(t_philo *p)
{
	if (printstate(p, SLEEP, now(p)) == 1)
		return (1);
	usleep(p->info->ttslp);
	return (0);
}

int	think(t_philo *p)
{
	if (printstate(p, THINK, now(p)) == 1)
		return (1);
	usleep(p->info->ttthk);
	return (0);
}

int	philo_routine(t_philo *p)
{
	set_time(p);
	while (1)
	{
		if (p->info->phqty < 2)
			continue ;
		sem_wait(p->info->sem_go);
		if (grab_fork(p) == 0 && grab_fork(p) == 0)
		{
			sem_post(p->info->sem_go);
			if (eat(p) == 1 || nap(p) == 1 || think(p) == 1)
				endr(p);
		}
		else
			endr(p);
	}
	return (0);
}
