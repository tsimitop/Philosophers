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

void	sleep_loop(t_philosopher *phil, t_state state, time_t time)
{
	time_t	wake;

	wake = 0;
	if (state == SLEEPING)
		wake = (phil->shared_info->t_to_sleep) + init_time();
	else if (state == THINKING)
		wake = time + init_time();
	else if (state == EATING)
		wake = (phil->shared_info->t_to_eat) + init_time();
// printf("wake = %li\n", wake);
// printf("init_time() = %li\n", init_time());
// printf("phil[%i]->your_time_has_come = %li\n", phil->thread_idx, phil->your_time_has_come);
	if (phil->your_time_has_come <= time_since_start(phil->shared_info))
	{
// printf("phil[%i]->your_time_has_come = %li\n", phil->thread_idx, phil->your_time_has_come);
		pthread_mutex_lock(&phil->shared_info->death_lock);
		phil->shared_info->death_occured = true;
		pthread_mutex_unlock(&phil->shared_info->death_lock);
printf("sleep_loop 111111\n");
// exit(0);
	}
	usleep(time / 2);
	if (phil->your_time_has_come <= time_since_start(phil->shared_info))
	{
// printf("phil[%i]->your_time_has_come = %li\n", phil->thread_idx, phil->your_time_has_come);
		pthread_mutex_lock(&phil->shared_info->death_lock);
		phil->shared_info->death_occured = true;
		pthread_mutex_unlock(&phil->shared_info->death_lock);
printf("sleep_loop 22222222\n");
// exit(0);
	}
	while (wake > init_time())
	{
		usleep(50);
		if (phil->your_time_has_come <= time_since_start(phil->shared_info))
		{
			pthread_mutex_lock(&phil->shared_info->death_lock);
// printf("phil[%i]->your_time_has_come = %li\n", phil->thread_idx, phil->your_time_has_come);
			phil->shared_info->death_occured = true;
			pthread_mutex_unlock(&phil->shared_info->death_lock);
printf("sleep_loop 333333\n");
// exit(0);
		}
	}
}
