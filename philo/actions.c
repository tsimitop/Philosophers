#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	time_t	cur_time;

	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	cur_time = time_since_start(phil->shared_info);
	printf(CYAN"%li %i has taken left fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	cur_time = time_since_start(phil->shared_info);
	printf(CYAN"%li %i has taken right fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
	cur_time = time_since_start(phil->shared_info);
	printf(BLUE"%li %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
	phil->last_meal_timestamp = cur_time;
	sleep_loop(phil, EATING, phil->shared_info->t_to_eat);
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

static void ft_sleep(t_philosopher *phil)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
	sleep_loop(phil, SLEEPING, phil->shared_info->t_to_sleep);
}

static void ft_think(t_philosopher *phil)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
}

void *routine(void *ptr)
{
	t_philosopher *philosoph;

	philosoph = (t_philosopher *)ptr;
	if (!philosoph || !philosoph->shared_info)
	{
		printf("Philosopher or shared_info is NULL\n");
		//KANE ERROR HANDLING
	}
	run_actions(philosoph);
	return NULL;
}

static void	run_actions(t_philosopher *phil)
{
	time_t	cur_time;

	if (phil->thread_idx % 2 != 0)
	{
		cur_time = time_since_start(phil->shared_info);
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		sleep_loop(phil, THINKING, 100);
	}
	while (time_since_start(phil->shared_info) < 3000)
	{
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil);
	}
}
