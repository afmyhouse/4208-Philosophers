
#include "philo_bonus.h"

t_philo	*philo_new(int id, t_info *data)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	ft_bzero(p, sizeof(t_philo));
	p->id = id;
	p->d = data;
	return (p);
}

void	philo_add(t_philo **p, t_philo *new)
{
	t_philo	*tmp;

	if (!*p)
	{
		*p = new;
		return ;
	}
	tmp = *p;
	while (tmp->id != new->id - 1)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = *p;
	(*p)->prev = new;
}

t_philo	*philo_init(t_info *data)
{
	int		i;
	t_philo	*p;
	t_philo	*new;

	p = NULL;
	new = NULL;
	i = 0;
	while (++i <= data->phqty)
	{
		new = philo_new(i, data);
		if (!new)
		{
			philofree(p);
			free_data(data);
			return (NULL);
		}
		philo_add(&p, new);
	}
	return (p);
}

int	set_processes(t_philo *p)
{
	t_philo		*tmp;
	int			i;
	pthread_t	thread;

	tmp = p;
	i = p->d->phqty;
	set_offset(p);
	while (i--)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (1);
		else if (tmp->pid == 0)
		{
			if (pthread_create(&thread, NULL, &bigbrother, tmp) != 0)
				return (1);
			if (pthread_detach(thread) != 0)
				return (1);
			exit(philo_routine(tmp));
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	seminit(t_info *data)
{
	sem_unlink("forks");
	data->sem_forks = sem_open("forks", O_CREAT, 0644, data->phqty);
	if (data->sem_forks == SEM_FAILED)
		return (1);
	sem_unlink("print");
	data->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		return (1);
	sem_unlink("death");
	data->sem_death = sem_open("death", O_CREAT, 0644, 1);
	if (data->sem_death == SEM_FAILED)
		return (1);
	sem_unlink("go");
	data->sem_go = sem_open("go", O_CREAT, 0644, data->phqty / 2);
	if (data->sem_go == SEM_FAILED)
		return (1);
	sem_unlink("end");
	data->sem_end = sem_open("end", O_CREAT, 0644, 0);
	if (data->sem_end == SEM_FAILED)
		return (1);
	sem_unlink("time");
	data->sem_time = sem_open("time", O_CREAT, 0644, 1);
	if (data->sem_time == SEM_FAILED)
		return (1);
	return (0);
}
