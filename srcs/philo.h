/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 17:00:15 by emlamoth         ###   ########.fr       */
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
# define ERRMAXVAL "200 philo max and between 60 and MAXINT ms\n"

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
	int	nb_philo;
	time_t	ttd;
	time_t	tts;
	time_t	tte;
	int	nb_time;
}				t_param;

typedef struct s_fork
{
	pthread_mutex_t fork;
	bool			locked;
}				t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			left_fork;
	t_fork			*right_fork;
	pthread_mutex_t *print_lock;
	pthread_mutex_t *meal_lock;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	bool			*dead;
	int				nb_time;
	int				nb_philo;
	time_t			last_meal;
	time_t			start;
}				t_philo;

typedef struct s_data
{
	t_param			param;
	t_philo			philo[200];
	pthread_t		thread[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	fork_lock;
	time_t			start;
	bool			dead;
	int				meals;
	
}				t_data;

//---------- univers.c
t_philo		*new_philo();
t_philo		*last_philo(t_philo *philo);
void		add_philo(t_philo **philo, t_philo *new_philo);
void		bigbang(t_data *data);
void		bigcrunch(t_data *data);

//---------- debug.c
void		print_param(t_data *data);

//---------- util2.c
int			ft_isdigit(int c);
long int	ft_atoi(const char *str);

//---------- util.c
int			err_handler(char *msg);
int			time_calc(struct timeval start_time);
bool		mutex_dead(t_philo *philo, int opt);
void		mutex_print(t_philo *philo, char *msg);
time_t		get_time(void);
void		new_sleep(unsigned long duration, t_philo *philo);

//---------- init_data.c
int			digit_argv(char **argv);
long int	ft_max_min(long int nbr);
void		check_max_param(time_t *param, char *arg);
int			build_base_param(t_data *data, char **argv);
t_data		*ft_init_data(t_data *data, char **argv);
t_data		*struct_data(t_data *ptr);

//---------- main.c
void		*routine(void	*data);
void		ft_init_philo(t_data *data, t_philo *philo);
int			time_calc(struct timeval start_time);
void		ft_init_fork(t_data *data);
void		mutex_print(t_philo *philo, char *msg);
bool		take_fork(t_philo *philo);
void		drop_fork(t_philo *philo);

//---------- utility.c
long int	ft_max_min(long int nbr);

//---------- thread_util.c
int			join_thread(t_data *data);
void		process_start(t_data *data);
void		clean_mutex(t_data *data);

//---------- routine.c
int	philo_eat(t_philo *philo);
int	philo_sleep(t_philo *philo);
void	*routine(void *philoptr);

#endif