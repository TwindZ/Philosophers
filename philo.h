/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/01 16:33:30 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>
# include <sys/time.h>
# include <pthread.h>

# define ERRNBPARAM "parameter error\n./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philosopher_must_eat(optional)]\n"

# define ERRINTMAX "parameter must be under max integer"
# define ERRONLYNB "only positif numeric argument are used by philo\n"
# define ERRMAXVAL "too high parameter value\n"

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
	int				dead;
	int				ttd;
	int				tte;
	int				tts;
	pthread_mutex_t fork;
	pthread_t 		thread;
	struct s_philo 	*right;
}				t_philo;

typedef struct s_data
{
	t_param		param;
	t_time		time;
	t_philo		*philo;
}				t_data;

long int	ft_atoi(const char *str);
int			ft_isdigit(int c);
t_philo		*new_philo(t_data *data);

#endif