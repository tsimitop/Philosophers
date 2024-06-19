#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		printf("Correct input is:\n./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (1);
	}
	if (ft_isnumber(argv) == false || ft_isnegative(argv) == true)
		return (1);
	return (0);
}

// void	error_exit(char *msg)
// {
// 	printf(msg);
// 	exit(1);
// }
