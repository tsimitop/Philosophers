#include "philo.h"

bool	ft_isnumber(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_hasalpha(argv[i]) == true)
		{
			printf("please provide integer parameters\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_isnegative(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || \
	ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		printf("Can accept only positive integer parameters\n");
		return (true);
	}
	if (argv[5] && ft_atoi(argv[5]) <= 0)
	{
		printf("Can accept only positive integer parameters\n");
		return (true);
	}
	return (false);
}

bool	ft_hasalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '-' && i == 0)
			i++;
		if (ft_isdigit(str[i]) == false)
			return (true);
		i++;
	}
	return (false);
}

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' || str[i] == '+')
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

bool	invalid_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Correct input is:\n./philo number_of_philos time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (true);
	}
	if (ft_isnumber(argv) == false || ft_isnegative(argv) == true || \
	init_time() < 0)
		return (true);
	return (false);
}
