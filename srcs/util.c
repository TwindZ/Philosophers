/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:54:21 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 11:17:10 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int err_handler(char *msg)
{
	printf("%s", msg);
	return (-1);
}

int	time_calc(struct timeval start_time)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return(((time.tv_usec - start_time.tv_usec) / 1000)
			+ ((time.tv_sec - start_time.tv_sec) * 1000));
	
}

bool	mutex_dead(t_philo *philo, int opt)
{
	bool	status;
	
	status = false;
	pthread_mutex_lock(philo->dead_lock);
	if(opt)
	{
		if(*philo->dead == false)
			printf("%d %d %s", time_calc(philo->time), philo->id, "dead\n");
		*philo->dead = true;
	}
	else
		status = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return(status);
}

void	mutex_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print_lock);
	if(mutex_dead(philo, 0) == false)
		printf("%d %d %s", time_calc(philo->time), philo->id, msg);
	pthread_mutex_unlock(philo->print_lock);
	
}