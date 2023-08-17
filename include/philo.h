/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/17 15:39:09 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//---------- DEFINE
#ifndef PHILO_H
# define PHILO_H

# define ERRNBPARAM "parameter error\n./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat(optional)]\n"

# define ERRINTMAX "parameter must be under max integer\n"
# define ERRONLYNB "only positif numeric argument are used by philo\n"
# define ERRMAXVAL "parameter must be between 1 to 1000 philo and 60 to \
100000000 ms\n"

# define THINK "is thinking\n"
# define SLEEP "is sleeping\n"
# define EAT "is eating\n"
# define FORK "has taken a fork\n"
# define DEAD "dead\n"

//---------- INCLUDE
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

//---------- STRUCT
typedef struct s_param
{
	int				nb_philo;
	time_t			ttd;
	time_t			tts;
	time_t			tte;
	int				nb_time;
}				t_param;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	bool			locked;
}				t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*meal_lock;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	bool			*dead;
	int				nb_time;
	int				nb_philo;
	time_t			last_meal;
	time_t			start;
}					t_philo;

typedef struct s_data
{
	t_param			param;
	t_philo			philo[1000];
	pthread_t		thread[1000];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	fork_lock;
	time_t			start;
	bool			dead;
	int				meals;
}				t_data;

//---------- debug.c
void		print_param(t_data *data);

//---------- util2.c
int			ft_isdigit(int c);
long int	ft_atoi(const char *str);

//---------- util.c
int			err_handler(char *msg);
bool		mutex_dead(t_philo *philo);
void		mutex_print(t_philo *philo, char *msg);
time_t		get_time(void);
void		new_sleep(unsigned long duration, t_philo *philo);

//---------- init.c
int			digit_argv(char **argv);
long int	ft_max_min(long int nbr);
void		check_max_param(time_t *param, char *arg);
int			build_base_param(t_data *data, char **argv);
void		init_philo(t_data *data, t_philo *philo);
t_data		*init_data(t_data *data, char **argv);
t_data		*struct_data(t_data *ptr);

//---------- main.c

//---------- thread_util.c
int			join_thread(t_data *data);
void		monitoring(t_data *data);
void		process_start(t_data *data);
void		clean_mutex(t_data *data);

//---------- routine.c
void		*philo_alone(void *philoptr);
void		philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
void		*routine(void *philoptr);

//---------- monitoring.c
void		monitoring(t_data *data);
#endif