#include "philo.h"

int	main(int argc, char **argv)
{
	t_shared		info;
	t_philosopher	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Correct input is:\n./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (1);
	}
	if (ft_isnumber(argv) == false || ft_isnegative(argv) == true || init_time(&info) == 1)
		return (1);
	init_shared(&info, argv);
	if (info.initial_timestamp < 0)
		return (1);
	init_philosopher(&info, &philo);
	return (0);
}

// int	init_mutex(t_shared *info, t_philosopher *philo)
// {

// }

int	init_thread(t_shared *info, t_philosopher *philo)
{
	pthread_t	thread;
	int			i;
	int			j;

	j = 0;
	i = info->philos_total;
	info->philo = (t_philosopher *)malloc(info->philos_total + 1);
	while (i > 0)
	{
		pthread_create(info->philo[j], NULL, NULL, NULL);
		// pthread_create(NULL, routine, NULL, NULL);
		init_philosopher(info, info->philo[j]);
		pthread_mutex_init(philo[j].left_fork, NULL);
		pthread_mutex_init(philo[j].right_fork, NULL);
		j++;
		i--;
	}
	info->philo[j] = NULL;
	pthread_join(thread, NULL);
}

void	init_philosopher(t_shared *info, t_philosopher *philo)
{
	philo->state = THINKING;
	philo->dead = false;
	philo->ate_x_times = 0;
	philo->last_meal_timestamp = info->initial_timestamp;
	philo->time_since_last_meal = 0;
	// philo->left_fork = pthread_mutex_init(uuum, NULL);
	// philo->right_fork = NULL;
}

void	init_shared(t_shared *info, char **argv)
{
	info->philos_total = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if(argv[5])
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = 2147483640;
	info->death_occured = false;
	info->initial_timestamp = init_time();
}

// void	error_exit(char *msg)
// {
// 	printf(msg);
// 	exit(1);
// }
