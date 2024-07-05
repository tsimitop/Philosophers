#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	int		r_fork;
	int		l_fork;
	time_t	cur_time;

	r_fork = phil->thread_idx - 1;
	l_fork = (phil->thread_idx) % phil->shared_info->philos_total;
	pthread_mutex_lock(phil->shared_info->fork[r_fork]);
	cur_time = time_since_start(phil->shared_info);
	printf(CYAN"%li %i has taken right fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
	cur_time = time_since_start(phil->shared_info);
	pthread_mutex_lock(phil->shared_info->fork[l_fork]);
	printf(CYAN"%li %i has taken left fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
	cur_time = time_since_start(phil->shared_info);
	printf(BLUE"%li %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
	phil->last_meal_timestamp = cur_time;
	phil->state = EATING;
	sleep_loop(phil, phil->state, phil->shared_info->t_to_eat);
	pthread_mutex_unlock(phil->shared_info->fork[l_fork]);
	pthread_mutex_unlock(phil->shared_info->fork[r_fork]);
}

static void ft_sleep(t_philosopher *phil)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
	phil[phil->thread_idx].state = SLEEPING;
	sleep_loop(phil, phil->state, phil->shared_info->t_to_sleep);
}

static void ft_think(t_philosopher *phil, time_t time)
{
	time_t	cur_time;

	cur_time = time_since_start(phil->shared_info);
	if (cur_time - phil->last_meal_timestamp > 50)
	{
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		sleep_loop(phil, THINKING, time);
	}
}


static void	pick_up_fork(t_philosopher *phil)
{
	time_t	cur_time;
	int		r_fork;
	int		l_fork;

	r_fork = phil->thread_idx - 1;
	l_fork = (phil->thread_idx) % phil->shared_info->philos_total;
	if (phil->thread_idx % 2 == 0)
	{
		cur_time = time_since_start(phil->shared_info);
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		sleep_loop(phil, THINKING, 100);
	}
	while (1)
	{
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil, 100);
	}
}

void *routine(void *ptr)
{
	t_philosopher *philosoph;

	philosoph = (t_philosopher *)ptr;
	if (!philosoph || !philosoph->shared_info)
	{
		printf("Philosopher or shared_info is NULL\n");
		pthread_exit(NULL);
	}
	run_actions(philosoph);
	return NULL;
}

static void	run_actions(t_philosopher *philosoph)
{
	int	idx;

	idx = 0;
	while (idx < philosoph[idx].shared_info->philos_total)
	{
		pick_up_fork(philosoph);
		idx++;
	}
}
