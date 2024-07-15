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

int	sleep_loop(t_philosopher *phil, t_state state, time_t time)
{
	time_t	wake;

	wake = 0;
	if (state == SLEEPING)
		wake = (phil->shared_info->t_to_sleep) + init_time();
	else if (state == THINKING)
		wake = time + init_time();
	else if (state == EATING)
		wake = (phil->shared_info->t_to_eat) + init_time();

		//alla3e to gia sleep na mhn tsekarei thanato
	// if (boring_death_checkup(phil) == true)
	// 	return (1);
	if (time > phil->your_time_has_come - phil->shared_info->t_to_eat) //time > phil->your_time_has_come || 
		return (1);
	usleep(time / 2);
	// if (boring_death_checkup(phil) == true)
	// 	return (1);
	while (wake > init_time())
	{
		usleep(1000);
	}
	// if (boring_death_checkup(phil) == true)
	// 	return (1);
	// if (phil->shared_info->death_occured == true)
	// 	printf("sleep_loop: DEATH OCCURED\n");
	// if (phil->shared_info->all_philos_stuffed == true)
	// 	printf("sleep_loop: ALL PHILOS STUFFED\n");
	// if (phil->shared_info->death_occured == false)
	// 	printf("sleep_loop: DEATH DID NOT OCCUR\n");
	// if (phil->shared_info->all_philos_stuffed == false)
	// 	printf("sleep_loop: NOT ALL PHILOS STUFFED\n");
	return (0);
}
