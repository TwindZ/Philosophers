/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:42:50 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/09 16:14:06 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	digit_argv(char **argv)
{
	int i;
	int j;

	i = 1;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if(ft_isdigit(argv[i][j]) == 0)
				return(0);
			j++;
		}
		i++;
	}
	return (1);
}
long int ft_max_min(long int nbr)
{
	if(nbr >= -2147483648 && nbr <= 2147483647)
		return(1);
	return(0);
}

void	check_max_param(int *param, char *arg)
{
	long int nbr;
	
	nbr = ft_atoi(arg);
	if (ft_max_min(nbr))
		*param = nbr;
	else
		*param = -1;
}

int	build_base_param(t_data *data, char **argv)
{
	check_max_param(&data->param.nb_philo, argv[1]);
	check_max_param(&data->param.ttd, argv[2]);
	check_max_param(&data->param.tte, argv[3]);
	check_max_param(&data->param.tts, argv[4]);
	if(argv[5])
		check_max_param(&data->param.nb_time, argv[5]);
	else
		data->param.nb_time = -2;
	if (data->param.nb_philo == -1 || data->param.ttd == -1 
			|| data->param.tte == -1 || data->param.tts == -1 
			|| data->param.nb_time == -1)
			return (err_handler(ERRMAXVAL));
	return (0);
}
t_data	*struct_data(t_data *ptr)
{
	static t_data	*data = NULL;

	if(ptr)
		data = ptr;
	return (data);
}


t_data *ft_init_data(t_data *data, char **argv)
{
	build_base_param(data, argv);

	struct_data(data);
	return(data);
}

void	ft_init_philo(t_data *data, t_philo *philo)
{
	int i;
	
	i = 0;
	while(i < data->param.nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].ttd = data->param.ttd;
		philo[i].tte = data->param.tte;
		philo[i].tts = data->param.tts;
		philo[i].nb_time = data->param.nb_time;
		philo[i].dead = &data->dead;
		philo[i].print_lock = &data->print_lock;
		philo[i].dead_lock = &data->dead_lock;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		if(i == data->param.nb_philo - 1)
			philo[0].right_fork = &philo[i].left_fork;
		else
			philo[i + 1].right_fork = &philo[i].left_fork;
		i++;
	}
}