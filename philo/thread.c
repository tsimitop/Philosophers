#include "philo.h"

int init_thread(t_shared *info)
{
	int idx;
	// pthread_t supervisor;

	idx = 0;
	while (idx < info->philos_total)
	{
		if (pthread_create(&(info->philo[idx].philo_thread), NULL, routine, &(info->philo[idx])) != 0)
			return (printf("Failed to create thread\n"), 1);
		idx++;
	}
	// if (pthread_create(&supervisor, NULL, super_routine, info) != 0)
	// 	return (printf("Failed to create thread\n"), 1);
	// if (pthread_join(supervisor, NULL) != 0)
	// 	return (printf("Failed to create thread\n"), 1);
	printf("check line 19 in thread.c\n");
	death_checker(info);
	
	idx = 0;
// printf("info->philos_total = %i\n", info->philos_total);
	while (idx < info->philos_total)
	{
		pthread_join(info->philo[idx].philo_thread, NULL);
		idx++;
// printf("hiiiiiiii\n");
// printf("idx = %i\n", idx);
// printf("info->philos_total = %i\n", info->philos_total);
	}
	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_mutex_destroy(&info->fork[idx]);
		idx++;
	}
	return (0);
}
