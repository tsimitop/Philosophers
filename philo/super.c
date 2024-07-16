/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:18:56 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 17:27:31 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_death_flag_check(t_shared *info)
{
	int	idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_mutex_lock(&info->death_lock);
		if ((philo_surviving(info->philo[idx]) == false))
		{
			pthread_mutex_unlock(&info->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&info->death_lock);
		idx++;
	}
	return (0);
}

int	philos_stuffed_flag_check(t_shared *info)
{
	int	idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_mutex_lock(&info->death_lock);
		if (all_stuffed(info->philo[idx]) == true)
		{
			pthread_mutex_unlock(&info->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&info->death_lock);
		idx++;
	}
	return (0);
}

bool	philo_surviving(t_philosopher philo)
{
	if (philo.shared_info->death_occured == true)
		return (false);
	if (philo.your_time_has_come < time_since_start(philo.shared_info))
	{
		philo.shared_info->death_occured = true;
		pthread_mutex_unlock(&philo.shared_info->death_lock);
		ft_output(&philo, DIED);
		pthread_mutex_lock(&philo.shared_info->death_lock);
		return (false);
	}
	return (true);
}

bool	all_stuffed(t_philosopher philo)
{
	int	i;

	i = 0;
	if (philo.shared_info->all_philos_stuffed == true)
		return (true);
	while (philo.shared_info->philos_total > i)
	{
		if (philo.shared_info->philo[i].ate_x_times < \
		philo.shared_info->times_to_eat)
			break ;
		i++;
	}
	if (i == philo.shared_info->philos_total)
	{
		philo.shared_info->all_philos_stuffed = true;
		return (true);
	}
	return (false);
}

bool	boring_death_checkup(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->shared_info->death_lock);
	if (phil->shared_info->death_occured || \
	phil->shared_info->all_philos_stuffed)
		return (pthread_mutex_unlock(&phil->shared_info->death_lock), true);
	return (pthread_mutex_unlock(&phil->shared_info->death_lock), false);
}
