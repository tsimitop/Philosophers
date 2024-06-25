#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	GOT_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
} t_state;

typedef struct s_philosopher	t_philosopher;

typedef struct s_shared
{
	int						philos_total;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						times_to_eat;
	bool					death_occured;
	struct s_philosopher	**philo;
	long long				initial_timestamp;
} t_shared;

typedef struct s_philosopher
{
	enum e_state		state;
	bool				dead;
	int					ate_x_times;
	long long			last_meal_timestamp;
	long long			time_since_last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
} t_philosopher;

// void	error_exit(char *msg);

// parse.c
bool	ft_isnegative(char **argv);
int		ft_atoi(char *str);
bool	ft_hasalpha(char *str);
bool	ft_isdigit(int c);
bool	ft_isnumber(char **argv);

// time.c
int	init_time(void);

//init
void	init_shared(t_shared *info, char **argv);
void	init_philosopher(t_shared *info, t_philosopher *philo);

#endif
