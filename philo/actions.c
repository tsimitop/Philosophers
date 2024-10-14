/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:18:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 16:28:16 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_philosopher *phil)
{
	if (boring_death_checkup(phil) == true)
		return (1);
	if (lock_forks(phil) == 1)
		return (1);
	ft_output(phil, EATING);
	pthread_mutex_lock(&phil->shared_info->death_lock);
	phil->your_time_has_come = time_since_start(phil->shared_info) + \
	phil->shared_info->t_to_die;
	pthread_mutex_unlock(&phil->shared_info->death_lock);
	if (sleep_loop(phil, EATING, phil->shared_info->t_to_eat) == 1)
		return (unlock_forks(phil), 1);
	unlock_forks(phil);
	pthread_mutex_lock(&phil->shared_info->death_lock);
	phil->ate_x_times++;
	pthread_mutex_unlock(&phil->shared_info->death_lock);
	if (boring_death_checkup(phil) == true)
		return (1);
	return (0);
}

static int	ft_sleep(t_philosopher *phil)
{
	if (boring_death_checkup(phil) == true)
		return (1);
	ft_output(phil, SLEEPING);
	if (sleep_loop(phil, SLEEPING, phil->shared_info->t_to_sleep) == 1)
		return (1);
	return (0);
}

static int	ft_think(t_philosopher *phil)
{
	time_t	thinking_time;

	if (boring_death_checkup(phil) == true)
		return (1);
	ft_output(phil, THINKING);
	pthread_mutex_lock(&phil->shared_info->death_lock);
	thinking_time = phil->your_time_has_come - \
	time_since_start(phil->shared_info) - phil->shared_info->t_to_eat - 10;
	pthread_mutex_unlock(&phil->shared_info->death_lock);
	if (thinking_time > 0)
		sleep_loop(phil, THINKING, thinking_time);
	return (0);
}

void	*routine(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	if (!phil || !phil->shared_info)
		return (printf("Philosopher or shared_info is NULL\n"), NULL);
	if (phil->thread_idx % 2 != 1 || phil->thread_idx == phil.philos_total)
	{
		ft_output(phil, THINKING);
		if (sleep_loop(phil, THINKING, phil->shared_info->t_to_eat) == 1)
			return (NULL);
	}
	while (1)
	{
		if (ft_eat(phil) == 1)
			break ;
		if (ft_sleep(phil) == 1)
			break ;
		if (ft_think(phil) == 1)
			break ;
	}
	return (NULL);
}
