#include "philo.h"

//eat
//sleep
//think
//pick up fork
//routine

void	*routine(void *ptr)
{
	t_shared	*info;

	info = (t_shared *)ptr;
	printf("Vrexei kareklopodara\n");
	// printf("info->thread_idx = %i\n", info->thread_idx);
	printf("Astrapovrondá\n");
	return (NULL);
}