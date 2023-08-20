/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:54:21 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/20 12:19:44 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	err_handler(char *msg)
{
	printf("%s", msg);
	return (-1);
}

/* This function retrieves the time of day in milliseconds. */
time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

/*This function operates similarly to the 'usleep' function,
but the time is specified in milliseconds.*/
void	ms_sleep(unsigned long duration, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(philo->nb_philo * 2);
	}
}

/* This functionc check the dead status using a mutex to avoid interleaved output from
multiple threads. */
bool	mutex_dead(t_philo *philo)
{
	bool	status;

	status = false;
	pthread_mutex_lock(philo->meal_lock);
	status = *philo->dead;
	pthread_mutex_unlock(philo->meal_lock);
	return (status);
}

/* This function print using a mutex to avoid interleaved output from
multiple threads. */
void	mutex_print(t_philo *philo, char *msg)
{
	time_t	timestamp;

	timestamp = get_time() - philo->start;
	pthread_mutex_lock(philo->print_lock);
	if (mutex_dead(philo) == false)
		printf("%ld %d %s", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->print_lock);
}
