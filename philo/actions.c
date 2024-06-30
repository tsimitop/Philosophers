#include "philo.h"

static void	run_actions(t_shared *info);

//eat
//sleep
//think
//pick up fork
//routine

void	*routine(void *ptr)
{
	t_philosopher	*philosoph;
	// int				idx;

	// info = (t_shared *)ptr;
	philosoph = (t_philosopher *)ptr;
	// idx = 1;
	// printf("Vrexei kareklopodara\n");
	while (1)
	{
		// printf("philosoph->last_meal_timestamp = %lld\n", philosoph->last_meal_timestamp);
		// printf("philosoph->shared_info->time_to_die = %i\n", philosoph->shared_info->time_to_die);
		if (philosoph->shared_info->death_occured == true)
			break ;
		if (philosoph->shared_info->meals_remaining <= 0)
			break ;
		run_actions(philosoph->shared_info);
		printf("HEY\n");
		// idx++;
	}
	// printf("Astrapovrondá\n");
	return (NULL);
}

static void	run_actions(t_shared *info)
{
	printf("run_actions: picked up a fork\n");
	printf("run_actions: is eating\n");
	printf("run_actions: is sleeping\n");
	printf("run_actions: is thinking\n");
	(void)info;
}
