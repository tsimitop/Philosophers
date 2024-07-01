#include "philo.h"
//make && ./philo 5 800 200 200
int	main(int argc, char **argv)
{
	t_shared		*info;

	if (invalid_input(argc, argv) == true)
		return (1);
	info = ft_calloc(1, sizeof(t_shared));
	init_shared(info, argv);
	if (info->initial_timestamp < 0)
		return (1);
	if (init_thread(info))
		return (1);
	return (0);
}

void	init_shared(t_shared *info, char **argv)
{
	info->philos_total = ft_atoi(argv[1]);
	info->time_to_die = ft_atoll(argv[2]);
	info->time_to_eat = ft_atoll(argv[3]);
// printf("init_shared: info->time_to_eat = %lld\n", info->time_to_eat);
	info->time_to_sleep = ft_atoll(argv[4]);
	if(argv[5])
		info->times_to_eat = ft_atoll(argv[5]);
	else
		info->times_to_eat = 2147483640;
	info->meals_remaining = info->times_to_eat;
	// printf("info->times_to_eat = %i\n", info->times_to_eat);
	// printf("info->meals_remaining = %i\n", info->meals_remaining);
	info->death_occured = false;
	info->initial_timestamp = init_time();
	// info->forks = ft_calloc(1, sizeof(pthread_mutex_t *));
}
