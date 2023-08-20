/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/20 12:29:47 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*This function creates threads and initializes the start time for each one*/
void	process_start(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	if (data->param.nb_philo == 1)
	{
		data->philo[0].start = data->start;
		data->philo[0].last_meal = get_time();
		pthread_create(&data->thread[0], NULL, &philo_alone, &data->philo[0]);
	}
	else
	{
		while (i < data->param.nb_philo)
		{
			data->philo[i].start = data->start;
			data->philo[i].last_meal = get_time();
			pthread_create(&data->thread[i], NULL, &routine, &data->philo[i]);
			i++;
		}
	}
}
/* This function joins threads together after their execution. */
int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param.nb_philo)
		pthread_join(data->thread[i++], NULL);
	return (1);
}

/* This function cleans up all mutexes by destroying them. */
void	clean_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param.nb_philo)
		pthread_mutex_destroy(&data->philo[i++].left_fork);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->print_lock);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (err_handler(ERRNBPARAM));
	if (digit_argv(argv))
		return (err_handler(ERRONLYNB));
	if (!init_data(&data, argv))
		return (-1);
	init_philo(&data, data.philo);
	process_start(&data);
	monitoring(&data);
	join_thread(&data);
	clean_mutex(&data);
	return (0);
}
