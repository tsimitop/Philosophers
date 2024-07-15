#include "philo.h"

static int	run_actions(t_philosopher *info);

// static int	ft_eat(t_philosopher *phil)
// {
// 	time_t	cur_time;

// 	if (lock_forks(phil) == 1)
// 		return (1);
// 	ft_output(phil, EATING);
	
// 	pthread_mutex_lock(&phil->dining_lock);
// 	cur_time = init_time();
// 	phil->ate_x_times++;
// 	// if (boring_death_checkup(phil) == true)
// 	// 	return (unlock_forks(phil), 1);
// 	phil->last_meal_timestamp = cur_time;
// 	pthread_mutex_lock(&phil->death_lock);
// 	phil->your_time_has_come = phil->last_meal_timestamp + phil->shared_info->t_to_die;
// 	pthread_mutex_unlock(&phil->death_lock);
// 	pthread_mutex_unlock(&phil->dining_lock);
// 	// pthread_mutex_lock(&phil->dining_lock); //NEW
// 	if (sleep_loop(phil, EATING, phil->shared_info->t_to_eat) == 1)
// 	{
// // printf("ENTERED SLEEPING LOOP FAIL %i\n", phil->thread_idx);
// 	// pthread_mutex_unlock(&phil->dining_lock); //NEW

// 		return (unlock_forks(phil), 1);
// 	}
// 	// pthread_mutex_unlock(&phil->dining_lock); //NEW
	
// 	unlock_forks(phil);
// 	if (boring_death_checkup(phil) == true)
// 		return (1);
// // printf("REACHED EATING END\n");
// 	return (0);
// }

static int	ft_eat(t_philosopher *phil)
{
	if (boring_death_checkup(phil) == true)
		return (1);
	if (lock_forks(phil) == 1)							// FORKS
		return (1);
	ft_output(phil, EATING);

	pthread_mutex_lock(&phil->shared_info->death_lock);
	// pthread_mutex_lock(&phil->death_lock);				// DEATH
	phil->your_time_has_come = time_since_start(phil->shared_info) + phil->shared_info->t_to_die;
	// pthread_mutex_unlock(&phil->death_lock);			// DEATH
	pthread_mutex_unlock(&phil->shared_info->death_lock);

	if (sleep_loop(phil, EATING, phil->shared_info->t_to_eat) == 1)
		return (unlock_forks(phil), 1);
	
	unlock_forks(phil);									// FORKS
	pthread_mutex_lock(&phil->shared_info->death_lock);

	// pthread_mutex_lock(&phil->dining_lock);				// DINING
	phil->ate_x_times++;
	// pthread_mutex_unlock(&phil->dining_lock);			// DINING
	pthread_mutex_unlock(&phil->shared_info->death_lock);

	if (boring_death_checkup(phil) == true)
		return (1);
	return (0);
}

bool	boring_death_checkup(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->shared_info->death_lock);

	if (phil->shared_info->death_occured || phil->shared_info->all_philos_stuffed)
		return (pthread_mutex_unlock(&phil->shared_info->death_lock), true);
	return (pthread_mutex_unlock(&phil->shared_info->death_lock), false);
}

int	lock_forks(t_philosopher *phil)
{
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	if (boring_death_checkup(phil) == true)
	{
		if (phil->thread_idx % 2 == 0)
			return (pthread_mutex_unlock(&phil->shared_info->fork[phil->l_fork_idx]), 1);
		else
			return (pthread_mutex_unlock(&phil->shared_info->fork[phil->r_fork_idx]), 1);
	}
	ft_output(phil, GOT_FORK);
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	if (boring_death_checkup(phil) == true)
		return (unlock_forks(phil), 1);
	ft_output(phil, GOT_FORK);
	return (0);
}

void	unlock_forks(t_philosopher *phil)
{
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
static int ft_sleep(t_philosopher *phil)
{
	time_t	cur_time;

	if (boring_death_checkup(phil) == true)
		return (1);
	cur_time = time_since_start(phil->shared_info);
	printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
	if (sleep_loop(phil, SLEEPING, phil->shared_info->t_to_sleep) == 1)
		return (1);
// printf("SLEEPING END\n");
	return (0);
}

static int ft_think(t_philosopher *phil)
{
	time_t	cur_time;
	time_t thinking_time;

	if (boring_death_checkup(phil) == true)
		return (1);
	cur_time = time_since_start(phil->shared_info);
	// printf("cur_time = %li\n", cur_time);
	printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx); //ft_output!!!!!!!
	// pthread_mutex_lock(&phil->dining_lock);
	// pthread_mutex_lock(&phil->death_lock);
	pthread_mutex_lock(&phil->shared_info->death_lock);

	// printf("time_since_start(phil->shared_info) = %li\n", time_since_start(phil->shared_info));
	// printf("phil->your_time_has_come - init_time() = %li\n", phil->your_time_has_come - init_time());

	thinking_time = phil->your_time_has_come - time_since_start(phil->shared_info) - phil->shared_info->t_to_eat - 10;
	pthread_mutex_unlock(&phil->shared_info->death_lock);
	// pthread_mutex_unlock(&phil->death_lock);
	if (thinking_time > 0)
		sleep_loop(phil, THINKING, thinking_time);
	// thinking_time = (phil->your_time_has_come - time_since_start(phil->shared_info)) - phil->shared_info->t_to_die - 10;
	// thinking_time = phil->shared_info->t_to_die - (init_time() - phil->last_meal_timestamp) - 10;
// printf("thinking_time = %li\n", thinking_time);
	// pthread_mutex_unlock(&phil->dining_lock);
// printf("THINKING END\n");
	return (0);
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
	return (NULL);
}

static int	run_actions(t_philosopher *phil)
{
	time_t	cur_time;

	if (phil->thread_idx % 2 != 1)
	{
		cur_time = time_since_start(phil->shared_info);
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
		if (sleep_loop(phil, THINKING, phil->shared_info->t_to_eat) == 1)
			return (1);
	}
	while (1)
	{
		if (ft_eat(phil) == 1)
		{
// printf("thread[%i] EAT failed at %li \n", phil->thread_idx, time_since_start(phil->shared_info));
			return (1);
		}
		if (ft_sleep(phil) == 1)
		{
// printf("thread[%i] SLEEP failed at %li \n", phil->thread_idx, time_since_start(phil->shared_info));
			return (1);
		}
		if (ft_think(phil) == 1)
		{
// printf("thread[%i] THINK failed at %li \n", phil->thread_idx, time_since_start(phil->shared_info));
			return (1);
		}
	}
	return (0);
}
