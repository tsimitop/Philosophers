/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:01 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 14:25:18 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	joiner(t_shared *info);

int	init_thread(t_shared *info)
{
	int	idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		if (pthread_create(&info->philo[idx].philo_thread, NULL, \
		routine, &info->philo[idx]) != 0)
			return (ft_exit_program("Failed to create thread\n", info, idx), 1);
		idx++;
	}
	while (1)
	{
		if (philos_death_flag_check(info))
			break ;
		if (philos_stuffed_flag_check(info))
			break ;
		usleep(1000);
	}
	joiner(info);
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
	return (0);
}

void	joiner(t_shared *info)
{
	int	idx;

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
}

void	ft_exit_program(char *msg, t_shared *info, int idx)
{
	if (msg)
		printf("%s", msg);
	if (idx > 0)
	{
		idx = 0;
		while (pthread_join(info->philo[idx].philo_thread, NULL) == 0)
			idx++;
	}
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
}
