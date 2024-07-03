#include "philo.h"
//make && ./philo 5 800 200 200
int	main(int argc, char **argv)
{
	t_shared		info;

	if (invalid_input(argc, argv) == true)
		return (1);
	if (init_shared(&info, argv))
		return (1);
	if (init_thread(&info))
		return (1);
	return (0);
}

int	init_shared(t_shared *info, char **argv)
{
	info->philos_total = ft_atoi(argv[1]);
	info->t_to_die = ft_atoi(argv[2]);
	info->t_to_eat = ft_atoi(argv[3]);
	info->t_to_sleep = ft_atoi(argv[4]);
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
		return (pthread_mutex_destroy(&info->death_lock), \
		printf("Mutex initialization failed\n"), 1);
	info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	if (!info->philo)
		return (printf("info->philo allocation failed\n"), 1);
	info->fork = ft_calloc(info->philos_total, sizeof(pthread_mutex_t **));
	if (!info->fork)
		return (printf("info->fork allocation failed\n"), 1);
	int i = 0;
	while (info->philos_total > i)
	{
		info->fork[i] = ft_calloc(info->philos_total, sizeof(pthread_mutex_t *));
		if (!info->fork[i])
			return (printf("info->philo[idx].fork allocation failed\n"), 1);
		i++;
	}
	return (0);
}
