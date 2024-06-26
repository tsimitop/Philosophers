#include "philo.h"
//make && ./philo 5 800 200 200
int	main(int argc, char **argv)
{
	t_shared		info;
	t_philosopher	philo;

	if (invalid_input(argc, argv) == true)
		return (1);
	init_shared(&info, argv);
	if (info.initial_timestamp < 0)
		return (1);
	if (init_thread(&info, &philo))
		return (1);
	return (0);
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
