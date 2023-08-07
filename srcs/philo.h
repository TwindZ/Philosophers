/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/07 11:01:58 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//---------- DEFINE
#ifndef PHILO_H
# define PHILO_H

# define ERRNBPARAM "parameter error\n./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat(optional)]\n"

# define ERRINTMAX "parameter must be under max integer"
# define ERRONLYNB "only positif numeric argument are used by philo\n"
# define ERRMAXVAL "too high parameter value\n"

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

typedef struct s_time
{
	long int	start_sec;
	long int	start_usec;
	long int	count_usec;
}				t_time;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t left_fork;
	pthread_mutex_t *right_fork;
	bool			dead;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_time;
	struct	timeval	time;
}				t_philo;

typedef struct s_data
{
	t_param			param;
	t_time			time;
	t_philo			philo[200];
	pthread_t		thread[200];
	pthread_mutex_t	main_lock;
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

//---------- utility.c
long int	ft_max_min(long int nbr);
int			err_handler(char *msg);


#endif