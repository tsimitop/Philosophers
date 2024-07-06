#include "philo.h"

int init_thread(t_shared *info)
{
	int idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		if (pthread_create(&(info->philo[idx].philo_thread), NULL, routine, &(info->philo[idx])) != 0)
			return (printf("Failed to create thread\n"), 1);
		idx++;
	}
	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_join(info->philo[idx].philo_thread, NULL);
		idx++;
	}
	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_mutex_destroy(&info->fork[idx]);
		idx++;
	}
	return (0);
}
