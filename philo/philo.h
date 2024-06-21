#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_shared
{
	int			philos_total;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_to_eat;
	bool		death_occured;
	long long	initial_timestamp;
} t_shared;

// void	error_exit(char *msg);

// parse.c
bool	ft_isnegative(char **argv);
int		ft_atoi(char *str);
bool	ft_hasalpha(char *str);
bool	ft_isdigit(int c);
bool	ft_isnumber(char **argv);

// time.c
int	init_time(t_shared *info);


#endif
