#include "philo.h"

static void	run_actions(t_philosopher *info);

static void	ft_eat(t_philosopher *phil)
{
	time_t	cur_time;

	lock_forks(phil);
	ft_output(phil, EATING);
	cur_time = init_time();
	pthread_mutex_lock(&phil->dining_lock);
	phil->ate_x_times++;
	phil->last_meal_timestamp = cur_time;
	phil->your_time_has_come = phil->last_meal_timestamp + phil->shared_info->t_to_die;
	pthread_mutex_unlock(&phil->dining_lock);
	sleep_loop(phil, EATING, phil->shared_info->t_to_eat);
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
	while (1)
	{
		ft_eat(phil);
		ft_sleep(phil);
		ft_think(phil);
	}
}
bool	all_stuffed(t_shared *info)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->all_philos_stuffed)
			return (pthread_mutex_unlock(&info->death_lock), true);
		pthread_mutex_unlock(&info->death_lock);
		while (info->philos_total > i && info->philo[i].ate_x_times >= info->times_to_eat)
			i++;
		if (i == info->philos_total)
		{
			pthread_mutex_lock(&info->death_lock);
			info->all_philos_stuffed = true;
			pthread_mutex_unlock(&info->death_lock);
		}
	}
}
