/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:52:01 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 17:25:39 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_thread(t_data *data)
{
	int i;

	i = 0;
	while(i < data->param.nb_philo)
		pthread_join(data->thread[i++], NULL);
	return (1);
}
void	process_start(t_data *data)
{
	int i;

	i = 0;
	data->start = get_time();
	while(i < data->param.nb_philo)
	{
		data->philo[i].start = data->start;
		data->philo[i].last_meal = get_time();
		pthread_create(&data->thread[i], NULL, &routine, &data->philo[i]);
		i++;
	}
	while(1)
	{
		i = 0;
		while(i < data->param.nb_philo)
		{
			pthread_mutex_lock(&data->meal_lock);
			if((get_time() - data->philo[i].last_meal) >= data->param.tte)
				mutex_dead(&data->philo[i], 1);
			pthread_mutex_unlock(&data->meal_lock);
			i++;
		}
	}
}

void	clean_mutex(t_data *data)
{
	int i;

	i = 0;
	while(i < data->param.nb_philo)
	{
		
		pthread_mutex_destroy(&data->philo[i].left_fork.fork);
		i++;
	}
	pthread_mutex_destroy(&data->fork_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->print_lock);
}
	