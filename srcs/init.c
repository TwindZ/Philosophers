/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:42:50 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/17 15:39:04 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_max_param(time_t *param, char *arg)
{
	time_t	nbr;

	nbr = (time_t)ft_atoi(arg);
	if (nbr >= 60 && nbr <= 100000000)
		*param = nbr;
	else
		*param = -1;
}

int	build_base_param(t_data *data, char **argv)
{
	if (ft_atoi(argv[1]) <= 1000 && ft_atoi(argv[1]) > 0)
		data->param.nb_philo = ft_atoi(argv[1]);
	else
		data->param.nb_philo = -1;
	check_max_param(&data->param.ttd, argv[2]);
	check_max_param(&data->param.tte, argv[3]);
	check_max_param(&data->param.tts, argv[4]);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) >= 1 && ft_atoi(argv[5]) <= INT_MAX)
			data->param.nb_time = ft_atoi(argv[5]);
		else if (ft_atoi(argv[5]) == 0)
			return (-1);
		else
			data->param.nb_time = -1;
	}
	else
		data->param.nb_time = -2;
	if (data->param.nb_philo == -1 || data->param.ttd == -1 
		|| data->param.tte == -1 || data->param.tts == -1 
		|| data->param.nb_time == -1)
		return (err_handler(ERRMAXVAL));
	return (0);
}

t_data	*init_data(t_data *data, char **argv)
{
	if (build_base_param(data, argv) == -1)
		return (NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->fork_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	return (data);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->param.nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].ttd = data->param.ttd;
		philo[i].tte = data->param.tte;
		philo[i].tts = data->param.tts;
		philo[i].nb_time = data->param.nb_time;
		philo[i].nb_philo = data->param.nb_philo;
		philo[i].dead = &data->dead;
		philo[i].print_lock = &data->print_lock;
		philo[i].meal_lock = &data->meal_lock;
		pthread_mutex_init(&philo[i].left_fork.fork, NULL);
		if (i == data->param.nb_philo - 1)
			philo[0].right_fork = &philo[i].left_fork;
		else
			philo[i + 1].right_fork = &philo[i].left_fork;
		i++;
	}
}
