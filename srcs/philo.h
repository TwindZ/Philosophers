/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/10 11:10:38 by emlamoth         ###   ########.fr       */
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
# define ERRMAXVAL "too high parameter value\n"

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

//---------- STRUCT
typedef struct s_param
{
	int	nb_philo;
	int	ttd;
	int	tts;
	int	tte;
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
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *fork_lock;
	bool			*dead;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_time;
	struct	timeval	time;
}				t_philo;

typedef struct s_data
{
	t_param			param;
	t_philo			philo[200];
	pthread_t		thread[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	fork_lock;
	struct	timeval	time;
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

//---------- ft_atoi.c
int			ft_isdigit(int c);
long int	ft_atoi(const char *str);

//---------- init_data.c
int			digit_argv(char **argv);
long int	ft_max_min(long int nbr);
void		check_max_param(int *param, char *arg);
int			build_base_param(t_data *data, char **argv);
t_data		*ft_init_data(t_data *data, char **argv);
t_data		*struct_data(t_data *ptr);

//---------- main.c
void		*routine(void	*data);
void		ft_init_philo(t_data *data, t_philo *philo);
int			time_calc(struct timeval start_time);
void		ft_init_fork(t_data *data);
void		mutex_print(t_philo *philo, char *msg, int opt);

//---------- utility.c
long int	ft_max_min(long int nbr);
int			err_handler(char *msg);


#endif