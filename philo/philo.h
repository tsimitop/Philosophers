#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define QUIT_COLOR "\033[0m"

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
	int					philos_total;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					times_to_eat;
	bool				death_occured;
	long long			initial_timestamp;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		printer_lock;
	t_philosopher		*philo;
	pthread_mutex_t		**fork;
} t_shared;

typedef struct s_philosopher
{
	pthread_t			philo_thread;
	int					thread_idx;
	enum e_state		state;
	int					die_phil;
	bool				dead;
	int					ate_x_times;
	long long			last_meal_timestamp;
	long long			time_since_last_meal;
	pthread_mutex_t		*dining_lock;
	pthread_mutex_t		*sleeping_lock;
	t_shared			*shared_info;
	// pthread_mutex_t		*fork;
	// pthread_mutex_t		*l_fork;
} t_philosopher;

// parse.c
bool	ft_isnumber(char **argv);
bool	ft_isnegative(char **argv);
bool	ft_hasalpha(char *str);
bool	ft_isdigit(int c);
int		ft_atoi(char *str);
bool	invalid_input(int argc, char **argv);

// time.c
long long	init_time(void);
void	sleep_loop(t_philosopher *philosoph, t_state state, long long time);
int		time_since_start(t_shared *info);

//init
int		init_shared(t_shared *info, char **argv);
int		init_philosopher(t_shared *info, int idx);
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
