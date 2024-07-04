#include "philo.h"

time_t	init_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	time_since_start(t_shared *info)
{
	int	current_time;

	current_time = init_time() - info->initial_timestamp;
	return (current_time);
}

void	sleep_loop(t_philosopher *phil, t_state state, long long time)
{
	time_t	wake;

	wake = 0;
	// pthread_mutex_lock(&phil->state_lock);
	if (state == SLEEPING)
		wake = (phil->shared_info->t_to_sleep) + init_time();
	else if (state == THINKING)
		wake = time + init_time(); //change
	else if (state == EATING)
		wake = (phil->shared_info->t_to_eat) + init_time();
// printf("wake = %li\tinit_time() = %li\n", wake, init_time());
	if (state == SLEEPING || state == THINKING)
	{
		// pthread_mutex_lock(&phil->sleeping_lock);
		usleep(time / 2);
		while (wake > init_time())
		{
			usleep(50);
		}
		// pthread_mutex_unlock(&phil->sleeping_lock);
	}
	else if (state == EATING)
	{
		// pthread_mutex_lock(&phil->dining_lock);
		usleep(time / 2);
		while (wake > init_time())
		{
			usleep(50);
		}
		// pthread_mutex_unlock(&phil->dining_lock);
	}
	// pthread_mutex_unlock(&phil->state_lock);
}
