#include "philo.h"
void	joiner(t_shared *info); //fiiiiiiiix

int init_thread(t_shared *info)
{
	int idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		// if (pthread_create(&(info->philo[idx].philo_thread), NULL, routine, &(info->philo[idx])) != 0)
		// 	return (ft_exit_program("Failed to create thread\n", info, idx), 1);
		if (pthread_create(&(info->philo[idx].philo_thread), NULL, routine, &(info->philo[idx])) != 0)
			return (printf("Failed to create thread\n"), 1);
		idx++;
	}
	// if (death_checker(info) == 1)
	// 	return (ft_exit_program(NULL, info, idx), 0);
	// death_checker(info);
	// if ((death_checker(info) == 1) || (all_stuffed(info) == true))
	while (1)
	{
		int	idx;

		idx = 0;
		while (idx < info->philos_total)
		{
			if ((philo_surviving(info->philo[idx])) == false)
			{
				printf("death_checker BREAK!!!\n");
				joiner(info);
				return (0);
			}
			idx++;
		}
		idx = 0;
		while (idx < info->philos_total)
		{
			if (all_stuffed(info->philo[idx]) == true)
			{
				printf("all_stuffed BREAK!!!\n");
				joiner(info);
				return (0);
			}
			idx++;
		}
		// if (all_stuffed(info) == true)
		// {
		// 	printf("all_stuffed BREAK!!!\n");
		// 	joiner(info);
		// 	return (0);
		// }
	}
	joiner(info);
	return 0;

	// if (death_checker(info) == 1)
	// {
	// 	// return (pthread_mutex_destroy(&info->fork[idx]), 0);
	// 	return (pthread_join(info->philo[idx].philo_thread, NULL), pthread_mutex_destroy(&info->fork[idx]), 0);
	// }

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
	ft_exit_program(NULL, info, info->philos_total);
	return (0);
}

void	joiner(t_shared *info)
{
	int	idx;

	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_join(info->philo[idx].philo_thread, NULL);
		idx++;
	}
	idx = 0;
	while (idx < info->philos_total)
	{
		pthread_mutex_destroy(&info->fork[idx]);
		idx++;
	}
}

void	ft_exit_program(char *msg, t_shared *info, int idx)
{
	if (msg)
		printf("%s", msg);
	if (idx > 0)
	{
		--idx;
		while (idx > 0)
		{
			// pthread_join(info->philo[idx].philo_thread, NULL);
			// pthread_mutex_destroy(&info->fork[idx]);
			pthread_mutex_destroy(&info->philo[idx].death_lock);
			pthread_mutex_destroy(&info->philo[idx].dining_lock);
			idx--;
		}
	}
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
	// free(info->philo);
	// free(info->fork);
	// while (idx < info->philos_total)
	// {
	// 	if (info.philo[idx])
	// 	idx++;
	// }
}

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
