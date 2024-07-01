#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	pick_up_fork(t_philosopher *phil, int idx)
{
	(void)idx;
	while (1)
	{
		pthread_mutex_init(&phil->shared_info->forks[phil->thread_idx], NULL);
		printf("\033[0;36m%lli %i has taken a fork\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		pthread_mutex_init(&phil->shared_info->forks[phil->thread_idx + 1], NULL);
		printf("\033[0;36m%lli %i has taken a fork\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		printf("%lli %i is eating\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		phil[phil->thread_idx].state = EATING;
		sleep_loop(phil, phil[phil->thread_idx].state, phil->shared_info->time_to_eat);
		pthread_mutex_destroy(&phil->shared_info->forks[phil->thread_idx]);
		pthread_mutex_destroy(&phil->shared_info->forks[phil->thread_idx + 1]);
		printf("\033[0;35m%lli %i is sleeping\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		phil[phil->thread_idx].state = SLEEPING;
		sleep_loop(phil, phil[phil->thread_idx].state, phil->shared_info->time_to_sleep);
		printf("\033[0;32m%lli %i is thinking\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
	}
}

//pick up fork
//eat
//sleep
//think
//routine

void	*routine(void *ptr)
{
	t_philosopher	*philosoph;
	// int				idx;

	// info = (t_shared *)ptr;
	philosoph = (t_philosopher *)ptr;
	// idx = 1;
	// printf("Vrexei kareklopodara\n");
	// while (1)
	// {
		// printf("philosoph->last_meal_timestamp = %lld\n", philosoph->last_meal_timestamp);
		// printf("philosoph->shared_info->time_to_die = %i\n", philosoph->shared_info->time_to_die);

		// if (philosoph->shared_info->death_occured == true)
		// 	break ;
		// if (philosoph->shared_info->meals_remaining <= 0)
		// 	break ;
		run_actions(philosoph);
		// idx++;
// 	}
	// printf("Astrapovrondá\n");
	return (NULL);
}

static void	run_actions(t_philosopher *philosoph)
{
	int	idx;

	idx = 1;
	// printf("run_actions: picked up a fork\n");
	// printf("run_actions: is eating\n");
	// printf("run_actions: is sleeping\n");
	// printf("run_actions: is thinking\n");
	while (idx < philosoph->shared_info->philos_total + 1)
	{
		pick_up_fork(philosoph, idx);
		idx++;
	}
}
