/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:16 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 17:24:00 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*uc;

	i = 0;
	uc = s;
	while (i < n)
	{
		uc[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_output(t_philosopher *phil, t_state state)
{
	time_t	cur_time;

	pthread_mutex_lock(&phil->shared_info->print_lock);
	cur_time = time_since_start(phil->shared_info);
	if (state == GOT_FORK && boring_death_checkup(phil) == false)
		printf(CYAN"%li %i has taken a fork\n"QUIT_COLOR, \
		cur_time, phil->thread_idx);
	else if (state == EATING && boring_death_checkup(phil) == false)
		printf(BLUE"%li %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
	else if (state == SLEEPING && boring_death_checkup(phil) == false)
		printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, \
		phil->thread_idx);
	else if (state == THINKING && boring_death_checkup(phil) == false)
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, \
		phil->thread_idx);
	else if (state == DIED)
		printf(YELLOW"%li %i died\n"QUIT_COLOR, cur_time, phil->thread_idx);
	pthread_mutex_unlock(&phil->shared_info->print_lock);
}
