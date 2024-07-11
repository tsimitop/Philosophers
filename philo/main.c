#include "philo.h"

int init_philo(t_shared *info);

bool	philo_surviving(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	if (philo->your_time_has_come < init_time())
	{
		pthread_mutex_unlock(&philo->death_lock);
		pthread_mutex_lock(&philo->shared_info->death_lock);
		ft_output(philo, DIED);
		philo->shared_info->death_occured = true;
		pthread_mutex_unlock(&(philo->shared_info->death_lock));
		return false;
	}
	else
	{
		pthread_mutex_unlock(&philo->death_lock);
		return true;
	}
}

int	death_checker(t_shared *info)
{
	while (1)
	{
		if ((philo_surviving(info->philo)) == false)
			return (1);
		else if (all_stuffed(info) == true)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared		info;

	if (invalid_input(argc, argv) || init_shared(&info, argv) \
	|| init_philo(&info) || init_thread(&info))
		return (1);
	//NA TA KATASTREPSOOOOOOO KI ELEFTHEROSO
	free(info.fork);
	free(info.philo);
	return (0);
}

int init_philo(t_shared *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->philos_total)
	{
		info->philo[idx].thread_idx = idx + 1;
		info->philo[idx].ate_x_times = 0;
		info->philo[idx].last_meal_timestamp = info->initial_timestamp;
		info->philo[idx].time_since_last_meal = 0;
		info->philo[idx].shared_info = info;
		info->philo[idx].r_fork_idx = idx;
		info->philo[idx].l_fork_idx = (idx + 1) % info->philos_total;
		info->philo[idx].your_time_has_come = info->initial_timestamp + info->t_to_die;
		if (pthread_mutex_init(&info->fork[idx], NULL) != 0)
			return (printf("Failed to create thread\n"), 1);
	}
	return (0);
}

int	shared_mutex_allocations(t_shared *info)
{
	info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	if (!info->philo)
		return (pthread_mutex_destroy(&info->death_lock), \
		pthread_mutex_destroy(&info->print_lock), \
		printf("info->philo allocation failed\n"), 1);
	info->fork = ft_calloc(info->philos_total, sizeof(pthread_mutex_t));
	if (!info->fork)
		return (pthread_mutex_destroy(&info->death_lock), \
		pthread_mutex_destroy(&info->print_lock), \
		printf("info->fork allocation failed\n"), 1);
	return (0);
}

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
	if (pthread_mutex_init(&info->print_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info->death_lock), 
		printf("Mutex initialization failed\n"), 1);
	if (shared_mutex_allocations(info) == 1)
		return (1);
	return (0);
}
