#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	time_t	cur_time;

	lock_forks(phil);
	if (philo_surviving(phil) == false)
		return ;
	pthread_mutex_lock(&phil->shared_info->death_lock);
	// if (phil->your_time_has_come - phil->shared_info->t_to_eat > init_time())
	// {
	// 	pthread_mutex_lock(&phil->death_lock);
	// 	phil->dead = true;
	// 	pthread_mutex_unlock(&phil->death_lock);
	// 	// pthread_mutex_lock(&phil->shared_info->death_lock);
	// 	phil->shared_info->death_occured = true;
	// 	pthread_mutex_unlock(&phil->shared_info->death_lock);
	// 	return ;
	// }
	pthread_mutex_unlock(&phil->shared_info->death_lock);
	sleep_loop(phil, EATING, phil->shared_info->t_to_eat);
	ft_output(phil, EATING);
	// cur_time = time_since_start(phil->shared_info);
	cur_time = init_time();
	pthread_mutex_lock(&phil->dining_lock);
	phil->last_meal_timestamp = cur_time;
	pthread_mutex_unlock(&phil->dining_lock);
	if (philo_surviving(phil) == false)
	{
		// pthread_mutex_unlock(&phil->dining_lock);
		return ;
	}
	pthread_mutex_lock(&phil->dining_lock);
	phil->your_time_has_come = phil->last_meal_timestamp + phil->shared_info->t_to_die;
	// pthread_mutex_lock(&phil->dining_lock);
	phil->ate_x_times++;
	if (phil->ate_x_times == phil->shared_info->times_to_eat)
	{
		phil->philo_stuffed = true;
	}
	pthread_mutex_unlock(&phil->dining_lock);
	unlock_forks(phil);
}

void	lock_forks(t_philosopher *phil)
{
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	ft_output(phil, GOT_FORK);
	if (phil->thread_idx % 2 == 0)
		pthread_mutex_lock(&phil->shared_info->fork[phil->r_fork_idx]);
	else
		pthread_mutex_lock(&phil->shared_info->fork[phil->l_fork_idx]);
	ft_output(phil, GOT_FORK);
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


static void ft_sleep(t_philosopher *phil)
{
	ft_output(phil, SLEEPING);
	sleep_loop(phil, SLEEPING, phil->shared_info->t_to_sleep);
}

static void ft_think(t_philosopher *phil)
{
	ft_output(phil, THINKING);
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
	while ((philo_surviving(phil)) == true)
	{
// printf("ITERATE run_actions\n");
		// pthread_mutex_lock(&phil->shared_info->death_lock);
		if ((philo_surviving(phil)) == false)
		{
			printf("run_actions TRUE!\treturn from run_actions\n");
			return ;
		}
		pthread_mutex_unlock(&phil->shared_info->death_lock);
		ft_eat(phil);
		if (philo_surviving(phil) == false)
		{
			printf("run_actions TRUE!\treturn from run_actions\n");
			return ;
		}
		ft_sleep(phil);
		if (philo_surviving(phil) == false)
		{
			printf("run_actions TRUE!\treturn from run_actions\n");
			return ;
		}
		ft_think(phil);
		if (philo_surviving(phil) == false)
		{
			printf("run_actions TRUE!\treturn from run_actions\n");
			return ;
		}
	}
}

bool	philo_surviving(t_philosopher *phil)
{
	time_t	cur_timestamp;
	
	cur_timestamp = init_time();
	// cur_timestamp = init_time();
	pthread_mutex_lock(&phil->dining_lock);
	if (cur_timestamp >= phil->your_time_has_come)
	{
printf("PHILO NOT SURVIVING\n");
		pthread_mutex_lock(&phil->death_lock);
		phil->dead = true;
		pthread_mutex_unlock(&phil->death_lock);
		pthread_mutex_lock(&phil->shared_info->death_lock);
		phil->shared_info->death_occured = true;
		pthread_mutex_unlock(&phil->shared_info->death_lock);
	pthread_mutex_unlock(&phil->dining_lock);
		return (false);
	}
printf("PHILO SURVIVING JUST FINE\n");
	pthread_mutex_unlock(&phil->dining_lock);
	return (true);
}
