#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	time_t	cur_time;

	lock_forks(phil);
	ft_output(phil, EATING);
	cur_time = time_since_start(phil->shared_info);
	phil->last_meal_timestamp = cur_time;
	sleep_loop(phil, EATING, phil->shared_info->t_to_eat);
	phil->your_time_has_come = phil->last_meal_timestamp + phil->shared_info->t_to_die; 
	pthread_mutex_lock(&phil->dining_lock);
	phil->ate_x_times++;
// printf("phil->ate_x_times = %i\t", phil->ate_x_times);
// printf("phil->shared_info->times_to_eat = %i\n", phil->shared_info->times_to_eat);
	if (phil->ate_x_times == phil->shared_info->times_to_eat)
	{
// printf("sdlhafkjfhiuartoagpaiugipagiauhgiauehgiuaeghipahugripuahegipuhaeguergiha\n");
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
	// while (!phil->shared_info->death_occured && time_since_start(phil->shared_info) < 5000)
	while (1)
	{
		pthread_mutex_lock(&phil->shared_info->death_lock);
		if (phil->shared_info->death_occured == true)
		{
			printf("run_actions TRUE!\n");
			// break ;
		}
		pthread_mutex_unlock(&phil->shared_info->death_lock);
		ft_eat(phil);
		if (philo_surviving(phil) == false)
			break ;
		ft_sleep(phil);
		if (philo_surviving(phil) == false)
			break ;
		ft_think(phil);
		if (philo_surviving(phil) == false)
			break ;
	}
}

bool	philo_surviving(t_philosopher *phil)
{
	time_t	cur_time;
	
	cur_time = time_since_start(phil->shared_info);
// printf("cur_time = %li\n", cur_time);
// printf("phil->your_time_has_come = %li\n", phil->your_time_has_come);
	if (cur_time > phil->your_time_has_come)
	{
		phil->dead = true;
		pthread_mutex_lock(&phil->shared_info->death_lock);
		phil->shared_info->death_occured = true;
		pthread_mutex_unlock(&phil->shared_info->death_lock);
		return (false);
	}
	return (true);
}
