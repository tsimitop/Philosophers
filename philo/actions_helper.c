/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:21:19 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 16:28:27 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_single_fork(t_philosopher *phil)
{
	if (phil->thread_idx % 2 == 0)
		return \
		(pthread_mutex_unlock(&phil->shared_info->fork[phil->l_fork_idx]), 1);
	else
		return \
		(pthread_mutex_unlock(&phil->shared_info->fork[phil->r_fork_idx]), 1);
	return (0);
}

int	lock_forks(t_philosopher *phil)
{
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	if (boring_death_checkup(phil) == true)
		return (unlock_single_fork(phil));
	ft_output(phil, GOT_FORK);
	if (phil->shared_info->philos_total == 1)
	{
		usleep(phil->shared_info->t_to_die * 1000);
		return (unlock_single_fork(phil));
	}
	else
	{
		if (phil->thread_idx % 2 == 0)
			pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
		else
			pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
		if (boring_death_checkup(phil) == true)
			return (unlock_forks(phil), 1);
		ft_output(phil, GOT_FORK);
	}
	return (0);
}

void	unlock_forks(t_philosopher *phil)
{
	if (phil->thread_idx % 2 == 0)
	{
		pthread_mutex_unlock(&phil->shared_info->fork[phil->r_fork_idx]);
		pthread_mutex_unlock(&phil->shared_info->fork[phil->l_fork_idx]);
	}
	else
	{
		pthread_mutex_unlock(&phil->shared_info->fork[phil->l_fork_idx]);
		pthread_mutex_unlock(&phil->shared_info->fork[phil->r_fork_idx]);
	}
}
