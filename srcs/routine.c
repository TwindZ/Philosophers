/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:31:24 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/17 15:44:06 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_alone(void *philoptr)
{
	t_philo	*philo;

	philo = (t_philo *)philoptr;
	pthread_mutex_lock(&philo->left_fork.fork);
	mutex_print(philo, FORK);
	new_sleep(philo->ttd, philo);
	pthread_mutex_unlock(&philo->left_fork.fork);
	return (NULL);
}

void	philo_eat(t_philo *philo)
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
}

void	*routine(void *philoptr)
{
	t_philo	*philo;

	philo = (t_philo *)philoptr;
	if (((philo->id % 2) == 1))
	{
		mutex_print(philo, THINK);
		new_sleep(philo->tte, philo);
	}
	while (1)
	{
		philo_eat(philo);
		pthread_mutex_lock(philo->meal_lock);
		if (--philo->nb_time == 0)
			philo->id = 0;
		pthread_mutex_unlock(philo->meal_lock);
		if (mutex_dead(philo) == true || philo->id == 0)
			return (NULL);
		mutex_print(philo, SLEEP);
		new_sleep(philo->tts, philo);
		mutex_print(philo, THINK);
		if (mutex_dead(philo) == true || philo->id == 0)
			return (NULL);
	}
	return (NULL);
}
