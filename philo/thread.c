#include "philo.h"

// int	init_thread(t_shared *info, t_philosopher *philo)
// {
// 	pthread_t	thread;
// 	int			i;
// 	int			j;

// 	j = 0;
// 	i = info->philos_total;
// 	info->philo = (t_philosopher *)malloc(info->philos_total + 1);
// 	while (i > 0)
// 	{
// 		pthread_create(info->philo[j], NULL, NULL, NULL);
// 		// pthread_create(NULL, routine, NULL, NULL);
// 		init_philosopher(info, info->philo[j]);
// 		pthread_mutex_init(philo[j].left_fork, NULL);
// 		pthread_mutex_init(philo[j].right_fork, NULL);
// 		j++;
// 		i--;
// 	}
// 	info->philo[j] = NULL;
// 	pthread_join(thread, NULL);
// }

int	init_thread(t_shared *info, t_philosopher *philo)
{
	int	idx;

	idx = 0;
	info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	if (!philo)
		return (1);
	info->forks = ft_calloc(info->philos_total, sizeof(pthread_mutex_t));
	if (!philo)
		return (free(info->philo), 1);
	while (info->philos_total - idx > 0)
	{
		init_philosopher(info, idx);
		idx++;
	}
	idx = 0;
	while (info->philos_total - idx > 0)
	{
		// printf("info->philo->thread_idx = %i\n", info->philo->thread_idx);
		// printf("info->philo->state = %i\n", info->philo->state);
		// printf("info->philo[idx].last_meal_timestamp = %lld\n", info->philo[idx].last_meal_timestamp);
		pthread_join(info->philo[idx].philo_thread, NULL);
		idx++;
	}
	return (0);
}

void	init_philosopher(t_shared *info, int idx)
{
	// philo->state = THINKING;
	// philo->dead = false;
	// philo->ate_x_times = 0;
	// philo->last_meal_timestamp = info->initial_timestamp;
	// philo->time_since_last_meal = info->initial_timestamp;
	// pthread_create(&info->philo[idx], NULL, NULL, NULL);
	info->thread_idx = idx;
	pthread_create(&info->philo[idx].philo_thread, NULL, &routine, NULL);
	info->philo[idx].state = THINKING;
	info->philo[idx].dead = false;
	info->philo[idx].ate_x_times = 0;
	info->philo[idx].last_meal_timestamp = info->initial_timestamp;
	info->philo[idx].time_since_last_meal = info->initial_timestamp;
	info->philo[idx].right_fork = &info->forks[idx];
	info->philo[idx].left_fork = &info->forks[(idx + 1) % info->philos_total];
}
