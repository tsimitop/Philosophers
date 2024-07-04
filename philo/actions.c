#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	pick_up_fork(t_philosopher *phil)
{
	int temp;
	long long	cur_time;
	int	r_fork;
	int	l_fork;

	r_fork = phil->thread_idx - 1;
	l_fork = (phil->thread_idx) % phil->shared_info->philos_total;
// printf("phil->thread_idx = %i r_fork = %i l_fork = %i\n", phil->thread_idx, r_fork, l_fork);
	temp = 0;
	if (phil->thread_idx % 2 == 0)
	{
		cur_time = time_since_start(phil->shared_info);
		printf(GREEN"%lli %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		sleep_loop(phil, THINKING, 100);
	}
	while (1)
	{
		cur_time = time_since_start(phil->shared_info);
		pthread_mutex_lock(phil->shared_info->fork[r_fork]);
		printf(CYAN"%lli %i has taken right fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
		pthread_mutex_lock(phil->shared_info->fork[l_fork]);
		printf(CYAN"%lli %i has taken left fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
		printf(BLUE"%lli %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
		phil->last_meal_timestamp = cur_time;
		pthread_mutex_lock(&phil->state_lock);
		phil->state = EATING;
		sleep_loop(phil, phil->state, phil->shared_info->t_to_eat);
		pthread_mutex_unlock(&phil->state_lock);
		pthread_mutex_unlock(phil->shared_info->fork[l_fork]);
		pthread_mutex_unlock(phil->shared_info->fork[r_fork]);
		printf(PURPLE"%lli %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
		pthread_mutex_lock(&phil->state_lock);
		phil[phil->thread_idx].state = SLEEPING;
		pthread_mutex_unlock(&phil->state_lock);
		pthread_mutex_lock(&phil->state_lock);
		sleep_loop(phil, phil->state, phil->shared_info->t_to_sleep);
		pthread_mutex_unlock(&phil->state_lock);
		if (cur_time - phil->last_meal_timestamp > 50)
		{
			printf(GREEN"%lli %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
			usleep(temp / 2);
			temp /= 2;
			while (temp > 50)
			{
				usleep(50);
				temp -= 50;
			}
		}
	}
}
// printf("___________DEBUG_________________\n");

void *routine(void *ptr)
{
	t_philosopher *philosoph;

	philosoph = (t_philosopher *)ptr;
	if (!philosoph || !philosoph->shared_info)
	{
		printf("Philosopher or shared_info is NULL\n");
		pthread_exit(NULL);
	}
// printf("philosoph = %p\n", philosoph);
// printf("philosoph->shared_info = %p\n", philosoph->shared_info);
	run_actions(philosoph);
	return NULL;
}

static void	run_actions(t_philosopher *philosoph)
{
	int	idx;

	idx = 0;
	// printf("philosoph->shared_info = %p\n", philosoph->shared_info);
	// printf("philosoph->shared_info->philos_total = %p\n", &philosoph->shared_info->philos_total);
	while (idx < philosoph[idx].shared_info->philos_total)
	{
		pick_up_fork(philosoph);
		idx++;
	}
}
