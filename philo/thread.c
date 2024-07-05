#include "philo.h"

int init_thread(t_shared *info)
{
	int idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		if (init_philosopher(info, idx))
			printf("Failed to initialize philosopher\n");
		idx++;
	}
	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_join(info->philo[idx].philo_thread, NULL);
		idx++;
	}
	return (0);
}

int init_philosopher(t_shared *info, int idx)
{
	info->philo[idx].thread_idx = idx + 1;
	// info->philo[idx].state = THINKING;
	info->philo[idx].dead = false;
	info->philo[idx].ate_x_times = 0;
	info->philo[idx].last_meal_timestamp = info->initial_timestamp;
	info->philo[idx].time_since_last_meal = 0;
	info->philo[idx].shared_info = info;
	if (pthread_mutex_init(&info->philo[idx].sleeping_lock, NULL) != 0)
		return (printf("Failed to create thread\n"), 1);
	if (pthread_mutex_init(&info->philo[idx].dining_lock, NULL) != 0)
		return (printf("Failed to create thread\n"), 1);
	// if (pthread_mutex_init(&info->philo[idx].state_lock, NULL) != 0)
	// 	return (printf("Failed to create thread\n"), 1);
	if (pthread_mutex_init(info->fork[idx], NULL) != 0)
		return (printf("Failed to create thread\n"), 1);
	// info->philo->l_fork = info->philo[info->philo[idx + 1].thread_idx % info->philos_total].fork;
	if (pthread_create(&info->philo[idx].philo_thread, NULL, routine, &info->philo[idx]) != 0)
		return (printf("Failed to create thread\n"), 1);
	return (0);
}
