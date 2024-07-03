#include "philo.h"

long long	init_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	time_since_start(t_shared *info)
{
	int	current_time;

	current_time = init_time() - info->initial_timestamp;
	return (current_time);
}

void	sleep_loop(t_philosopher *philosoph, t_state state, long long time)
{
	int	wake;

	wake = 0;
	if (state == SLEEPING)
		wake = philosoph->shared_info->t_to_sleep + time_since_start(philosoph->shared_info);
	else if (state == THINKING)
		wake = philosoph->shared_info->t_to_sleep + time; //change
	else if (state == EATING)
		wake = philosoph->shared_info->t_to_eat + time_since_start(philosoph->shared_info);
// printf("philosoph->shared_info->t_to_sleep = %i\n", philosoph->shared_info->t_to_sleep);
// printf("philosoph->shared_info->t_to_eat = %i\n", philosoph->shared_info->t_to_eat);
// printf("time_since_start(philosoph->shared_info) = %i\n", time_since_start(philosoph->shared_info));
// printf("philosoph->shared_info->t_to_sleep + time_since_start(philosoph->shared_info) = %i\n", philosoph->shared_info->t_to_sleep + time_since_start(philosoph->shared_info));
// printf("WAKE = %i\n", wake);
	if (state == SLEEPING || state == THINKING)
	{
		pthread_mutex_lock(philosoph->sleeping_lock);
		usleep(time / 2);
		while (wake > init_time())
			usleep(50);
		pthread_mutex_unlock(philosoph->sleeping_lock);
	}
	else if (state == EATING)
	{
		pthread_mutex_lock(philosoph->dining_lock);
		usleep(time / 2);
		while (wake > init_time())
			usleep(50);
		pthread_mutex_unlock(philosoph->dining_lock);
	}
}
