
#include "philo_bonus.h"

int	fork_drop(t_philo *p)
{
	if (sem_post(p->info->sem_forks) != 0)
	{
		printf("Error: sem_post (fork)\n");
		return (1);
	}
	return (0);
}

void	endr(t_philo *p)
{
	int	i;

	i = p->info->phqty;
	while (i--)
	{
		if (sem_post(p->info->sem_end) != 0)
		{
			printf("Error: sem_post (sem_end)\n");
			exit(1);
		}
	}
}

int	philo_waiter(t_philo *p)
{
	int		i;
	t_philo	*tmp;

	tmp = p;
	i = p->info->phqty;
	while (i--)
		sem_wait(p->info->sem_end);
	while (tmp->next != NULL && tmp->next != p)
	{
		kill(tmp->pid, SIGKILL);
		tmp = tmp->next;
	}
	kill(tmp->pid, SIGKILL);
	return (0);
}
