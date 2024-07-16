/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:18:34 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 16:29:09 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_shared *info)
{
	int	idx;

	idx = -1;
	info->initial_timestamp = init_time();
	while (++idx < info->philos_total)
	{
		info->philo[idx].thread_idx = idx + 1;
		info->philo[idx].ate_x_times = 0;
		info->philo[idx].r_fork_idx = idx;
		info->philo[idx].l_fork_idx = (idx + 1) % info->philos_total;
		info->philo[idx].your_time_has_come = info->t_to_die;
		info->philo[idx].shared_info = info;
		if (pthread_mutex_init(&info->fork[idx], NULL) != 0)
		{
			while (idx > 0)
				pthread_mutex_destroy(&info->fork[idx]);
			return (printf("Failed to init mutex\n"), 1);
		}
	}
	return (0);
}

int	shared_mutex_allocations(t_shared *info)
{
	info->philo = (t_philosopher *)malloc(info->philos_total * \
	sizeof(t_philosopher));
	if (!info->philo)
		return (pthread_mutex_destroy(&info->death_lock), \
		pthread_mutex_destroy(&info->print_lock), \
		printf("info->philo allocation failed\n"), 1);
	info->fork = (pthread_mutex_t *)malloc(info->philos_total * \
	sizeof(pthread_mutex_t));
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
	if (argv[5])
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = 2147483640;
	info->death_occured = false;
	info->all_philos_stuffed = false;
	info->initial_timestamp = init_time();
	if (info->initial_timestamp < 0)
		return (1);
	if (pthread_mutex_init(&info->death_lock, NULL) != 0)
		return (printf("Mutex initialization failed\n"), 1);
	if (pthread_mutex_init(&info->print_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info->death_lock), \
		printf("Mutex initialization failed\n"), 1);
	if (shared_mutex_allocations(info) == 1)
		return (1);
	return (0);
}

bool	invalid_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Correct input is:\n./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (true);
	}
	if (ft_isnumber(argv) == false || ft_isnegative(argv) == true || \
	init_time() < 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_shared		info;

	if (invalid_input(argc, argv) || init_shared(&info, argv) \
	|| init_philo(&info) || init_thread(&info))
		return (1);
	free(info.fork);
	free(info.philo);
	return (0);
}
