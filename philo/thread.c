#include "philo.h"

int init_thread(t_shared *info)
{
	int idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		if (pthread_create(&(info->philo[idx].philo_thread), NULL, routine, &(info->philo[idx])) != 0)
			return (printf("Failed to create thread\n"), 1);
		idx++;
	}
	if (death_checker(info) == 1)
		return (pthread_join(info->philo[idx].philo_thread, NULL), pthread_mutex_destroy(&info->fork[idx]), 0);
	// idx = 0;
	// while (idx < info->philos_total)
	// {
	// 	pthread_join(info->philo[idx].philo_thread, NULL);
	// 	idx++;
	// }
	// idx = 0;
	// while (idx < info->philos_total)
	// {
	// 	pthread_mutex_destroy(&info->fork[idx]);
	// 	idx++;
	// }
	return (0);
}

// void	ft_destroy(t_shared *info, int idx)
// {
// 	while (info.philo[idx])
// 	{
		
// 	}
// }

// bool	ft_exit(char *msg, t_data *data, int num, bool join)
// {
// 	int		i;
// 	bool	ret;

// 	if (msg != NULL)
// 		printf(ERROR "%s\n", msg);
// 	i = -1;
// 	ret = true;
// 	if (join == true)
// 	{
// 		while (++i < num)
// 			if (data->philo[i].thread)
// 				if (pthread_join(data->philo[i].thread, NULL) != 0)
// 					ret = false;
// 	}
// 	pthread_mutex_destroy(&data->lock_dead);
// 	pthread_mutex_destroy(&data->lock_done);
// 	pthread_mutex_destroy(&data->lock_print);
// 	while (data->philo != NULL && num--)
// 	{
// 		pthread_mutex_destroy(&data->philo[num].r_fork);
// 		pthread_mutex_destroy(&data->philo[num].lock_eating);
// 	}
// 	free(data->philo);
// 	return (ret);
// }
