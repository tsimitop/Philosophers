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
printf("phil->thread_idx = %i,\tr_fork = %i,\tl_fork = %i\n", phil->thread_idx, r_fork, l_fork);
	temp = 0;
// 	if (phil->thread_idx % 2 == 0)
// 	{
// 		pthread_mutex_lock(phil->sleeping_lock);
// cur_time = time_since_start(phil->shared_info);
// printf(GREEN"BEFORE LOOP %lli %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
// 		sleep_loop(phil, THINKING, 1500000);
// 		pthread_mutex_unlock(phil->sleeping_lock);
// 	}
	while (1)
	{
		cur_time = time_since_start(phil->shared_info);
printf("THREAD_IDX: %i\t(phil->thread_idx + 1) %% phil->shared_info->philos_total = %i\n", phil->thread_idx, (phil->thread_idx + 1) % phil->shared_info->philos_total);
		if (pthread_mutex_lock(phil->shared_info->fork[r_fork]) == 0)
		{
printf("HIIIn\n");
			printf(CYAN"%lli %i has taken right fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
// printf("phil->shared_info->fork[l_fork] = %p\n", &phil->shared_info->fork[l_fork]);
// printf("pthread_mutex_lock(phil->shared_info->fork[l_fork]) = %i\n", pthread_mutex_lock(phil->shared_info->fork[l_fork]));
			if (pthread_mutex_lock(phil->shared_info->fork[l_fork]) == 0)
			{
				printf(CYAN"%lli %i has taken left fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
				printf(BLUE"%lli %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
				// pthread_mutex_lock(phil->shared_info->fork[r_fork]);
				phil->last_meal_timestamp = cur_time;
				phil->state = EATING;
				sleep_loop(phil, phil->state, phil->shared_info->t_to_eat);
				pthread_mutex_unlock(phil->shared_info->fork[r_fork]);
printf("%lli %i has unlocked r_fork\n", cur_time, phil->thread_idx);
				pthread_mutex_unlock(phil->shared_info->fork[l_fork]);
printf("%lli %i has unlocked l_fork\n", cur_time, phil->thread_idx);
			}
		}
		printf(PURPLE"%lli %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
		phil[phil->thread_idx].state = SLEEPING;
		sleep_loop(phil, phil->state, phil->shared_info->t_to_sleep);
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
