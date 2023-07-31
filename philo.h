/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/31 16:48:00 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>
// # include <time.h>
# include <sys/time.h>

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

typedef struct s_data
{
	t_param	param;
	t_time	time;
}				t_data;

long int	ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif