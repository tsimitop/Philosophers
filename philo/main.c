#include "philo.h"

int init_philo(t_shared *info);

int	main(int argc, char **argv)
{
	t_shared		info;

	if (invalid_input(argc, argv) == true)
		return (1);
	if (init_shared(&info, argv))
		return (1);
	if (init_philo(&info))
		return (1);
	if (init_thread(&info))
		return (1);
	//NA TA KATASTREPSOOOOOOO KI ELEFTHEROSO
	return (0);
}

int init_philo(t_shared *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->philos_total)
	{
		info->philo[idx].thread_idx = idx + 1;
		// info->philo[idx].state = THINKING;
		info->philo[idx].dead = false;
		info->philo[idx].ate_x_times = 0;
		info->philo[idx].last_meal_timestamp = info->initial_timestamp;
		info->philo[idx].time_since_last_meal = 0;
		info->philo[idx].shared_info = info;

		info->philo[idx].r_fork_idx = (idx + 1) % info->philos_total;
		info->philo[idx].l_fork_idx = idx;
		if (pthread_mutex_init(&info->philo[idx].sleeping_lock, NULL) != 0)
			return (printf("Failed to create thread\n"), 1);
		if (pthread_mutex_init(&info->philo[idx].dining_lock, NULL) != 0)
			return (printf("Failed to create thread\n"), 1);
		// if (pthread_mutex_init(&info->philo[idx].state_lock, NULL) != 0)
		// 	return (printf("Failed to create thread\n"), 1);
		if (pthread_mutex_init(&info->fork[idx], NULL) != 0)
			return (printf("Failed to create thread\n"), 1);

	}
	// info->philo->l_fork = info->philo[info->philo[idx + 1].thread_idx % info->philos_total].fork;

	return (0);
}

// int init_philosopher(t_shared *info, int idx)
// {
// 	info->philo[idx].thread_idx = idx + 1;
// 	// info->philo[idx].state = THINKING;
// 	info->philo[idx].dead = false;
// 	info->philo[idx].ate_x_times = 0;
// 	info->philo[idx].last_meal_timestamp = info->initial_timestamp;
// 	info->philo[idx].time_since_last_meal = 0;
// 	info->philo[idx].shared_info = info;
// 	if (pthread_mutex_init(&info->philo[idx].sleeping_lock, NULL) != 0)
// 		return (printf("Failed to create thread\n"), 1);
// 	if (pthread_mutex_init(&info->philo[idx].dining_lock, NULL) != 0)
// 		return (printf("Failed to create thread\n"), 1);
// 	// if (pthread_mutex_init(&info->philo[idx].state_lock, NULL) != 0)
// 	// 	return (printf("Failed to create thread\n"), 1);
// 	if (pthread_mutex_init(&info->fork[idx], NULL) != 0)
// 		return (printf("Failed to create thread\n"), 1);
// 	// info->philo->l_fork = info->philo[info->philo[idx + 1].thread_idx % info->philos_total].fork;
// 	return (0);
// }

int	init_shared(t_shared *info, char **argv)
{
	info->philos_total = ft_atoi(argv[1]);
	info->t_to_die = (time_t)ft_atoll(argv[2]);
	info->t_to_eat = (time_t)ft_atoll(argv[3]);
	info->t_to_sleep = (time_t)ft_atoll(argv[4]);
	if(argv[5])
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = 2147483640;
	info->death_occured = false;
	info->initial_timestamp = init_time();
	if (info->initial_timestamp < 0)
		return (1);
	if (pthread_mutex_init(&info->death_lock, NULL) != 0)
		return (printf("Mutex initialization failed\n"), 1);
	if (pthread_mutex_init(&info->printer_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info->death_lock), 
		printf("Mutex initialization failed\n"), 1);
	// info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	info->philo = (t_philosopher *)malloc(info->philos_total * sizeof(t_philosopher));
	if (!info->philo)
		return (printf("info->philo allocation failed\n"), 1);
	// info->fork = ft_calloc(info->philos_total, sizeof(pthread_mutex_t *));
	// if (!info->fork)
	// 	return (printf("info->fork allocation failed\n"), 1); //FIX PROTECTION
	// int i = 0;
	// while (info->philos_total > i)
	// {
	// 	info->fork[i] = ft_calloc( 1, sizeof(pthread_mutex_t));
	// 	if (!info->fork[i])
	// 		return (printf("info->philo[idx].fork allocation failed\n"), 1); //FIX PROTECTION
	// 	i++;
	// }
	// info->fork = ft_calloc(info->philos_total, sizeof(pthread_mutex_t));
	info->fork = (pthread_mutex_t *)malloc(info->philos_total * sizeof(pthread_mutex_t));
	if (!info->fork)
		return (printf("info->fork allocation failed\n"), 1); //FIX PROTECTION
	// int i = 0;
	// while (info->philos_total > i)
	// {
	// 	info->fork[i] = ft_calloc( 1, sizeof(pthread_mutex_t));
	// 	if (!info->fork[i])
	// 		return (printf("info->philo[idx].fork allocation failed\n"), 1); //FIX PROTECTION
	// 	i++;
	// }
	return (0);
}
