/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:31:24 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 17:01:56 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork.fork);
	mutex_print(philo, FORK);
	pthread_mutex_lock(&philo->right_fork->fork);
	mutex_print(philo, FORK);
	mutex_print(philo, EAT);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	new_sleep(philo->tte, philo);
	pthread_mutex_unlock(&philo->left_fork.fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	mutex_print(philo, SLEEP);
	new_sleep(philo->tts, philo);
	if(mutex_dead(philo, 0) == true)
		return (1);
	return (0);
}

// int	philo_sleep(t_philo *philo)
// {
	
// 	return (0);
// }

void	*routine(void *philoptr)
{
	t_philo *philo;
	philo = (t_philo *)philoptr;
	if(((philo->id % 2) == 1))
	{
		mutex_print(philo, THINK);
		new_sleep(philo->tte, philo);
	}
	while(1)
	{	
		if(philo_eat(philo))
			return (NULL);
		mutex_print(philo, THINK);
	}
	return (NULL);
}