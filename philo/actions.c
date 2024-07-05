#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	time_t	cur_time;

	printf("phil->thread_idx = %i, phil->r_fork_idx = %i, phil->l_fork_idx = %i\n", phil->thread_idx, phil->r_fork_idx, phil->l_fork_idx);
	pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	cur_time = time_since_start(phil->shared_info);
	printf(CYAN"%li %i has taken left fork\n"QUIT_COLOR, cur_time, phil->thread_idx);

	pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	cur_time = time_since_start(phil->shared_info);
	printf(CYAN"%li %i has taken right fork\n"QUIT_COLOR, cur_time, phil->thread_idx);


	cur_time = time_since_start(phil->shared_info);
	printf(BLUE"%li %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
	phil->last_meal_timestamp = cur_time;
	// phil->state = EATING;
	sleep_loop(phil, EATING, phil->shared_info->t_to_eat);
// printf("phil->shared_info->fork[l_fork] = %p\n", &phil->shared_info->fork[l_fork]);
// printf("phil->shared_info->fork[r_fork] = %p\n", &phil->shared_info->fork[r_fork]);
	pthread_mutex_unlock(&phil->shared_info->fork[phil->r_fork_idx]);
	pthread_mutex_unlock(&phil->shared_info->fork[phil->l_fork_idx]);
}

static void ft_sleep(t_philosopher *phil)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
	// phil[phil->thread_idx].state = SLEEPING;
	// phil->state = SLEEPING;
	sleep_loop(phil, SLEEPING, phil->shared_info->t_to_sleep);
}

static void ft_think(t_philosopher *phil)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	// if (cur_time - phil->last_meal_timestamp > 50)
	// {
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		// sleep_loop(phil, THINKING, time);
	// }
}

void *routine(void *ptr)
{
	t_philosopher *philosoph;

	philosoph = (t_philosopher *)ptr;
	if (!philosoph || !philosoph->shared_info)
	{
		printf("Philosopher or shared_info is NULL\n");
		//KANE ERROR HANDLING
		// pthread_exit(NULL);
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
	while (time_since_start(phil->shared_info) < 2000)
	{
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil);
	}
}

// static void	pick_up_fork(t_philosopher *phil)
// {
// 	time_t	cur_time;

// 	if (phil->thread_idx % 2 == 0)
// 	{
// 		cur_time = time_since_start(phil->shared_info);
// 		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
// 		sleep_loop(phil, THINKING, 100);
// 	}
// 	while (1)
// 	{
// 		ft_eat(phil);
// 		ft_sleep(phil);
// 		ft_think(phil, 100);
// 	}
// }