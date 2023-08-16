/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:52:01 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 10:25:22 by emlamoth         ###   ########.fr       */
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
	gettimeofday(&data->time, NULL);
	while(i < data->param.nb_philo)
	{
		data->philo[i].time = data->time;
		pthread_create(&data->thread[i], NULL, &routine, &data->philo[i]);
		i++;
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
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print_lock);
}
	