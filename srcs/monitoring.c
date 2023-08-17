/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:25:13 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/17 16:42:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	philo_dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal) >= philo->ttd)
	{
		if (philo->id != 0)
		{
			printf("%ld %d %s", get_time() - philo->start, philo->id, "dead\n");
			*philo->dead = true;
		}
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	return (false);
}

void	monitoring(t_data *data)
{
	int	i;
	int	nb_philo_completed;

	i = 0;
	nb_philo_completed = 0;
	while (1)
	{
		i = 0;
		while (i < data->param.nb_philo)
		{
			pthread_mutex_lock(&data->meal_lock);
			if (philo_dead(&data->philo[i]) == true)
				return ;
			if (data->philo[i].nb_time == 0)
				nb_philo_completed++;
			pthread_mutex_unlock(&data->meal_lock);
			i++;
			usleep(50);
		}
		if (nb_philo_completed == data->param.nb_philo)
			return ;
	}
}
