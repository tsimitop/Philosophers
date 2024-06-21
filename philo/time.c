#include "philo.h"

int	init_time(t_shared *info)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (1);
	info->initial_timestamp = ((tv.tv_sec * 1000) + (tv.tv_usec * 1000));
	return (0);
}
