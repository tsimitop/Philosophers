/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:44 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/16 14:23:46 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}	t_state;

typedef struct s_philosopher	t_philosopher;

typedef struct s_shared
{
	int					philos_total;
	int					times_to_eat;
	bool				death_occured;
	bool				all_philos_stuffed;
	time_t				t_to_die;
	time_t				t_to_eat;
	time_t				t_to_sleep;
	time_t				initial_timestamp;
	t_philosopher		*philo;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*fork;
}	t_shared;

typedef struct s_philosopher
{
	int					thread_idx;
	int					ate_x_times;
	int					r_fork_idx;
	int					l_fork_idx;
	time_t				your_time_has_come;
	t_shared			*shared_info;
	pthread_t			philo_thread;
}	t_philosopher;

// parse.c
bool		ft_isnumber(char **argv);
bool		ft_isnegative(char **argv);
bool		ft_hasalpha(char *str);
bool		ft_isdigit(int c);
int			ft_atoi(char *str);
bool		invalid_input(int argc, char **argv);

// time.c
time_t		init_time(void);
int			sleep_loop(t_philosopher *philosoph, t_state state, time_t time);
time_t		time_since_start(t_shared *info);

//init
int			init_shared(t_shared *info, char **argv);
int			init_thread(t_shared *info);

//utils.c
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
long long	ft_atoll(const char *str);
void		ft_output(t_philosopher *phil, t_state state);

//actions.c
void		*routine(void *ptr);
int			lock_forks(t_philosopher *phil);
void		unlock_forks(t_philosopher *phil);
bool		all_stuffed(t_philosopher philo);

void		ft_exit_program(char *msg, t_shared *info, int idx);
bool		philo_surviving(t_philosopher philo);
bool		boring_death_checkup(t_philosopher *phil);
int			philos_death_flag_check(t_shared *info);
int			philos_stuffed_flag_check(t_shared *info);

#endif
