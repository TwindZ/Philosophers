/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:31:24 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 14:22:44 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think_and_fork(t_philo *philo)
{
		while(mutex_dead(philo, 0) == false)
		{
			if((time_calc(philo->time) - philo->elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
				return (1);
			}
			if(take_fork(philo) == true)
				break;
			usleep(40);
		}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	mutex_print(philo, EAT);
	philo->elapsed = time_calc(philo->time);
	while(mutex_dead(philo, 0) == false)
	{
		if((time_calc(philo->time) - philo->elapsed) == (philo->ttd))
		{
			if(mutex_dead(philo, 0) == false)
				mutex_dead(philo, 1);
				drop_fork(philo);
			return (1);
		}
		if((time_calc(philo->time) - philo->elapsed) == (philo->tte))
		{
			drop_fork(philo);
			break ;
		}
		usleep(40);
	}
	if(mutex_dead(philo, 0) == true)
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	mutex_print(philo, SLEEP);
	while(mutex_dead(philo, 0) == false)
	{
		// printf("%d - %d = %d > %d\n", time_calc(philo->time), elapsed, (time_calc(philo->time) - elapsed), life);
		if((time_calc(philo->time) - philo->elapsed) == (philo->ttd))
		{
			if(mutex_dead(philo, 0) == false)
				mutex_dead(philo, 1);
			return (1);
		}
		if((time_calc(philo->time) - philo->elapsed) == (philo->tte + philo->tts))
			break ;
		usleep(40);
	}	
	if(mutex_dead(philo, 0) == true)
		return (1);
	return (0);
}

void	*routine(void *philoptr)
{
	t_philo *philo;
	philo = (t_philo *)philoptr;

	philo->elapsed = 0;
	if(((philo->id & 1) == 1))
	{
		mutex_print(philo, THINK);
		while(1)
		{
			if((time_calc(philo->time) - philo->elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
				return (NULL);
			}
			if(time_calc(philo->time) == philo->tte)
				break ;
			usleep(40);
		}
	}
	while(1)
	{	
		if(philo_think_and_fork(philo))
			return (NULL);
		if(philo_eat(philo))
			return (NULL);
		if(philo_sleep(philo))
			return (NULL);
		mutex_print(philo, THINK);
		usleep(100);
	}
	return (NULL);
}