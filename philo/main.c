#include "philo.h"

int init_philo(t_shared *info);

bool	philo_surviving(t_philosopher *philo)
{
// printf("init_time() = %li\tphilo->shared_info->initial_timestamp = %li\tphilo->last_meal_timestamp = %li\t philo->shared_info->t_to_die = %li\n", init_time(), philo->shared_info->initial_timestamp, philo->last_meal_timestamp, philo->shared_info->t_to_die);
// printf("time_since_start(philo->shared_info) = %li\t(init_time() - philo->last_meal_timestamp) = %li\t philo->shared_info->t_to_die = %li\n", time_since_start(philo->shared_info), (init_time() - philo->last_meal_timestamp), philo->shared_info->t_to_die);
	pthread_mutex_lock(&philo->death_lock);
	if (philo->your_time_has_come < init_time())
	{
		pthread_mutex_unlock(&philo->death_lock);
		pthread_mutex_lock(&philo->shared_info->death_lock);
		ft_output(philo, DIED);
		philo->shared_info->death_occured = true;
		pthread_mutex_unlock(&(philo->shared_info->death_lock));
		return false;
	}
	else
	{
		pthread_mutex_unlock(&philo->death_lock);
		return true;
	}
}

int	death_checker(t_shared *info)
{
	while (1)
	{
		if ((philo_surviving(info->philo)) == false)
			return (printf("1 EXIT death_checker\n"), 1);
		else if (info->all_philos_stuffed == true)
			return (printf("2 EXIT death_checker\n"), 1);
	}
	return (0);
}

//____________________________________________________________
// void	check_for_deads(t_data *d, t_philosopher *p)
// {
// 	int	i;

// 	while (1)
// 	{
// 		i = 0;
// 		pthread_mutex_lock(&(d->flag_ate_mutex));
// 		if (d->flag_all_ate != 0)
// 		{
// 			pthread_mutex_unlock(&(d->flag_ate_mutex));
// 			break ;
// 		}
// 		pthread_mutex_unlock(&(d->flag_ate_mutex));
// 		while (d->times_to_eat != -1
// 			&& i < d->number_of_philo && p[i].times_ate >= d->times_to_eat)
// 			i++;
// 		if (i == d->number_of_philo)
// 		{
// 			pthread_mutex_lock(&(d->flag_ate_mutex));
// 			d->flag_all_ate = 1;
// 			pthread_mutex_unlock(&(d->flag_ate_mutex));
// 		}
// 		keep_checking(d, p);
// 		if (d->flag_dead == 1)
// 			break ;
// 	}
// }
//____________________________________________________________

int	main(int argc, char **argv)
{
	t_shared		info;

printf("check main.c line 38\n");
printf("check actions.c line 95");
	if (invalid_input(argc, argv) || init_shared(&info, argv) \
	|| init_philo(&info) || init_thread(&info))
		return (1);
	//NA TA KATASTREPSOOOOOOO KI ELEFTHEROSO
	free(info.fork);
	free(info.philo);
	return (0);
}

int init_philo(t_shared *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->philos_total)
	{
		info->philo[idx].thread_idx = idx + 1;
		// info->philo[idx].dead = false;
		info->philo[idx].ate_x_times = 0;
		info->philo[idx].last_meal_timestamp = info->initial_timestamp;
		info->philo[idx].time_since_last_meal = 0;
		info->philo[idx].shared_info = info;
		info->philo[idx].r_fork_idx = idx;
		info->philo[idx].l_fork_idx = (idx + 1) % info->philos_total;
		info->philo[idx].your_time_has_come = info->initial_timestamp + info->t_to_die;
		// if (pthread_mutex_init(&info->philo[idx].sleeping_lock, NULL) != 0)
		// 	return (printf("Failed to create thread\n"), 1);
		// if (pthread_mutex_init(&info->philo[idx].dining_lock, NULL) != 0)
		// 	return (printf("Failed to create thread\n"), 1);
		if (pthread_mutex_init(&info->fork[idx], NULL) != 0)
			return (printf("Failed to create thread\n"), 1);
	}
	return (0);
}

int	init_shared(t_shared *info, char **argv)
{
	info->philos_total = ft_atoi(argv[1]);
	info->t_to_die = (time_t)ft_atoll(argv[2]);
	info->t_to_eat = (time_t)ft_atoll(argv[3]);
	info->t_to_sleep = (time_t)ft_atoll(argv[4]);
	if(argv[5])
		info->times_to_eat = ft_atoi(argv[5]);
	else
		info->times_to_eat = 2147483640;
	info->death_occured = false;
	info->initial_timestamp = init_time();
	if (info->initial_timestamp < 0)
		return (1);
	if (pthread_mutex_init(&info->death_lock, NULL) != 0)
		return (printf("Mutex initialization failed\n"), 1);
	if (pthread_mutex_init(&info->printer_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info->death_lock), 
		printf("Mutex initialization failed\n"), 1);
	info->philo = ft_calloc(info->philos_total, sizeof(t_philosopher));
	if (!info->philo)
		return (pthread_mutex_destroy(&info->death_lock), pthread_mutex_destroy(&info->printer_lock), printf("info->philo allocation failed\n"), 1);
	info->fork = ft_calloc(info->philos_total, sizeof(pthread_mutex_t));
	if (!info->fork)
		return (pthread_mutex_destroy(&info->death_lock), pthread_mutex_destroy(&info->printer_lock), printf("info->fork allocation failed\n"), 1); //FIX PROTECTION
	return (0);
}
