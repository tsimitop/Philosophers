#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*uc;

	i = 0;
	uc = s;
	while (i < n)
	{
		uc[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_output(t_philosopher *phil, t_state state)
{
	time_t	cur_time;

	pthread_mutex_lock(&phil->shared_info->print_lock);
	cur_time = time_since_start(phil->shared_info);
	if (state == GOT_FORK)
		printf(CYAN"%li %i has taken a fork\n"QUIT_COLOR, cur_time, phil->thread_idx);
	else if (state == EATING)
		printf(BLUE"%li %i is eating\n"QUIT_COLOR, cur_time, phil->thread_idx);
	else if (state == SLEEPING)
		printf(PURPLE"%li %i is sleeping\n"QUIT_COLOR, cur_time, phil->thread_idx);
	else if (state == THINKING)
		printf(GREEN"%li %i is thinking\n"QUIT_COLOR, cur_time, phil->thread_idx);
	else if (state == DIED)
		printf(YELLOW"%li %i died\n"QUIT_COLOR, cur_time, phil->thread_idx);
	pthread_mutex_unlock(&phil->shared_info->print_lock);
}


// t_philo_worker_arg	*copy_philo_worker_arg(t_philo_worker_arg arg)
// {
// 	t_philo_worker_arg	*worker_arg;

// 	worker_arg = (t_philo_worker_arg *)malloc(sizeof(t_philo_worker_arg));
// 	worker_arg->env = arg.env;
// 	worker_arg->philo = arg.philo;
// 	return (worker_arg);
// }

// int	dispatch_philosophers(t_simulation *env)
// {
// 	int					idx;
// 	t_philo_worker_arg	worker_arg;

// 	idx = 0;
// 	while (idx < env->num_of_philosophers)
// 	{
// 		worker_arg.env = env;
// 		worker_arg.philo = &env->philos[idx];
// 		if (pthread_create(&env->philos[idx].worker, NULL, philo_worker, 
// 				copy_philo_worker_arg(worker_arg)))
// 			return (1);
// 		idx++;
// 	}
// 	return (0);
// }

// typedef struct s_philo
// {
// 	int					number;
// 	int					meals_eaten;
// 	enum e_philo_state	status;
// 	pthread_mutex_t		*left_fork;
// 	pthread_mutex_t		*right_fork;
// 	struct timeval		last_meal_at;
// 	pthread_mutex_t		eating_mutex;
// 	pthread_mutex_t		starvation_mutex;
// 	pthread_t			worker;
// 	int					died;
// }	t_philo;