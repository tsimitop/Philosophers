#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

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
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				times_to_eat;
	bool					death_occured;
	struct s_philosopher	*philo;
	int						meals_remaining;
	pthread_mutex_t			*forks;
	long long				initial_timestamp;
} t_shared;

typedef struct s_philosopher
{
	int					thread_idx;
	pthread_t			philo_thread;
	enum e_state		state;
	bool				dead;
	int					ate_x_times;
	long long			last_meal_timestamp;
	long long			time_since_last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_shared			*shared_info;
} t_philosopher;

// parse.c
bool	ft_isnumber(char **argv);
bool	ft_isnegative(char **argv);
bool	ft_hasalpha(char *str);
bool	ft_isdigit(int c);
int		ft_atoi(char *str);
bool	invalid_input(int argc, char **argv);

// time.c
int		init_time(void);
void	sleep_loop(t_philosopher *philosoph, t_state state, long long time);

//init
void	init_shared(t_shared *info, char **argv);
void	init_philosopher(t_shared *info, int idx);
int		init_thread(t_shared *info);

//utils.c
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
long long	ft_atoll(const char *str);

//actions.c
// void	*routine(t_shared *info);
// void	routine(void);
void	*routine(void *ptr);

#endif
