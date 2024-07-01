#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	pick_up_fork(t_philosopher *phil, int idx)
{
	int temp;

	temp = 0;
	(void)idx;
	while (1)
	{
printf("pthread_mutex_lock(&phil->shared_info->forks[phil->thread_idx]) = %i\n", pthread_mutex_lock(&phil->shared_info->forks[phil->thread_idx]));
// exit(0);
		if (pthread_mutex_lock(&phil->shared_info->forks[phil->thread_idx]) == 0)
			printf("\033[0;36m%lli %i has taken a fork\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		// pthread_mutex_lock(&phil->shared_info->forks[phil->thread_idx + 1], NULL);
		if (pthread_mutex_lock(&phil->shared_info->forks[phil->thread_idx + 1 % phil->shared_info->philos_total]) == 0)
		{
			printf("\033[0;36m%lli %i has taken a fork\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
			printf("%lli %i is eating\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
			phil->last_meal_timestamp = (init_time() - (phil->shared_info->initial_timestamp));
			phil[phil->thread_idx].state = EATING;
			sleep_loop(phil, phil[phil->thread_idx].state, phil->shared_info->time_to_eat);
		}
printf("\033[0;31mphil->last_meal_timestamp = %lli\033[0m\n", phil->last_meal_timestamp);
		pthread_mutex_unlock(&phil->shared_info->forks[phil->thread_idx]);
		pthread_mutex_unlock(&phil->shared_info->forks[phil->thread_idx + 1]);
		// pthread_mutex_destroy(&phil->shared_info->forks[phil->thread_idx]);
		// pthread_mutex_destroy(&phil->shared_info->forks[phil->thread_idx + 1]);
		printf("\033[0;35m%lli %i is sleeping\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
		phil[phil->thread_idx].state = SLEEPING;
		// sleep_loop(phil, phil[phil->thread_idx].state, phil[phil->thread_idx].shared_info->time_to_sleep); //SEGFAULT
		sleep_loop(phil, phil->state, phil->shared_info->time_to_sleep);
		// temp = ft_calloc(1, sizeof(int));
		// temp = (init_time()-phil[phil->thread_idx].shared_info->initial_timestamp) - phil[phil->thread_idx].last_meal_timestamp;
		temp = (init_time()-phil->shared_info->initial_timestamp) - phil->last_meal_timestamp;
		if ((init_time()-phil->shared_info->initial_timestamp) - phil->last_meal_timestamp > 50)
		{
// printf("1.init_time()-phil->shared_info->initial_timestamp = %lli\n2.phil->last_meal_timestamp = %lli\n3.init_time() - phil->last_meal_timestamp = %lli\n", init_time()-phil->shared_info->initial_timestamp, phil->last_meal_timestamp, (init_time()-phil->shared_info->initial_timestamp) - phil->last_meal_timestamp);
			printf("\033[0;32m%lli %i is thinking\033[0m\n", (init_time()-phil->shared_info->initial_timestamp), phil->thread_idx);
			usleep(temp / 2);
			temp /= 2;
			while (temp > 50)
			{
printf("\033[0;33mtemp = %i\033[0m\n", temp);
				usleep(50);
				temp -= 50;
			}
		}
	}
}
// printf("___________DEBUG_________________\n");

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
