/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:54:21 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 17:10:23 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int err_handler(char *msg)
{
	printf("%s", msg);
	return (-1);
}
time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	new_sleep(unsigned long duration, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(philo->nb_philo * 3);
	}
}

bool	mutex_dead(t_philo *philo, int opt)
{
	bool	status;
	
	status = false;
	pthread_mutex_lock(philo->meal_lock);
	if(opt)
	{
		if(*philo->dead == false)
			printf("%ld %d %s", get_time() - philo->start, philo->id, "dead\n");
		*philo->dead = true;
	}
	else
		status = *philo->dead;
	pthread_mutex_unlock(philo->meal_lock);
	return(status);
}

void	mutex_print(t_philo *philo, char *msg)
{
	time_t timestamp;

	timestamp = get_time() - philo->start;
	pthread_mutex_lock(philo->print_lock);
	if(mutex_dead(philo, 0) == false)
		printf("%ld %d %s", timestamp, philo->id, msg);
	pthread_mutex_unlock(philo->print_lock);
	
}