#include "philo.h"

int	init_thread(t_shared *info)
{
	int	idx;

	idx = 0;
	info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	if (!info->philo)
		return (1);
	info->forks = ft_calloc(info->philos_total, sizeof(pthread_mutex_t *));
	if (!info->philo)
		return (free(info->philo), 1);
	while (info->philos_total - (idx) > 0)
	{
		init_philosopher(info, idx + 1);
		idx++;
	}
	idx = 0;
	while (info->philos_total - (idx) > 0)
	{
	// printf("init_thread: info->philo[idx + 1].thread_idx = %i\n", info->philo[idx + 1].thread_idx);
		pthread_join(info->philo[idx + 1].philo_thread, NULL);
		idx++;
	}
	return (0);
}

void	init_philosopher(t_shared *info, int idx)
{
	info->philo[idx].thread_idx = idx;
	// printf("init_philosopher: info->philo[idx].thread_idx = %i\n", info->philo[idx].thread_idx);
	pthread_create(&info->philo[idx].philo_thread, NULL, routine, (void *)&info->philo[idx]);
	info->philo[idx].state = THINKING;
	info->philo[idx].dead = false;
	info->philo[idx].ate_x_times = 0;
	info->philo[idx].last_meal_timestamp = info->initial_timestamp;
	info->philo[idx].time_since_last_meal = 0;
	info->philo[idx].right_fork = &info->forks[idx];
	info->philo[idx].left_fork = &info->forks[(idx + 1) % info->philos_total];
	info->philo[idx].shared_info = info;
}
