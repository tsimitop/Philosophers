#include "philo.h"

void *super_routine(void *ptr)
{
	t_shared *info;
	int	i;

	i = 0;
	info = (t_shared *)ptr;

	while (all_philos_stuffed(info) == false) // && info->death_occured == false
	{
		// if (info->death_occured == true)
		// {
		// 	printf("super_routine TRUE!\n");
		// 	break ;
		// }
		if (info->philo[i].dead == true)
		{
			ft_output(&info->philo[i], DIED);
			break ;
		}
		i++;
	}
	return (NULL);
}

bool	all_philos_stuffed(t_shared *info)
{
	int i;
	int	check;

	i = 0;
	check = 1;
	while (info->philos_total > i)
	{
		if (info->philo[i].philo_stuffed == true)
			check = 1;
		else if (info->philo[i].philo_stuffed == false)
			check = 0;
		if (check == 0)
			return (false);
		i++;
	}
	return (true);
}
