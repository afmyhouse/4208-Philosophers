
#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_info	*d;
	t_philo	*p;

	if (invalid_argc(argc) == 1 || invalid_argv(argv) == 1)
		return (1);
	d = philo_info(argv);
	if (!d)
		return (1);
	p = philo_init(d);
	if (!p)
		return (1);
	if (seminit(d) == 1 || set_processes(p) == 1)
	{
		philofree(p);
		return (1);
	}
	philo_waiter(p);
	semdestroyer(d);
	philofree(p);
	return (0);
}
