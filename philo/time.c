#include "philo.h"

int	init_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleep_loop(t_philosopher *philosoph, t_state state, long long time)
{
	long long	wake;
	// int			g_time;

	// g_time = init_time();
	// printf("g_time = %i\n", g_time);
	if (state == SLEEPING)
		wake = philosoph->shared_info->time_to_sleep + init_time();
	else if (state == EATING)
		wake = philosoph->shared_info->time_to_eat + init_time();
	usleep(time / 2);
	if (state == SLEEPING)
	{
		while (wake > init_time())
			usleep(50);
	}
	else if (state == EATING)
	{
// printf("wake = %lld\nphilosoph->shared_info->time_to_eat = %lld\n", wake, philosoph->shared_info->time_to_eat);
// printf("time = %lld\n", time);
		// wake = philosoph->shared_info->time_to_eat + (long long)init_time();
		while (wake > init_time())
			usleep(50);
	}
	// else if (state == THINKING)
	// {
	// 	while (philosoph->shared_info->time_to_think < time)
	// 		usleep(50);
	// }
}
