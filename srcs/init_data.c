/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:42:50 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/02 15:48:03 by emlamoth         ###   ########.fr       */
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
	check_max_param(&data->param.nb_time, argv[5]);
	if (data->param.nb_philo == -1 || data->param.ttd == -1 
			|| data->param.tte == -1 || data->param.tts == -1 
			|| data->param.nb_time == -1)
			return (err_handler(ERRMAXVAL));
	return (0);
}

t_data *ft_init_data(char **argv)
{
	static t_data *data;
	struct timeval time;
	
	if(!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		if(!data)
			return (NULL);
		if(build_base_param(data, argv) == -1)
			return (ft_freenull((void **)&data));
		if(gettimeofday(&time, NULL) == -1)
			return (ft_freenull((void **)&data));
		data->time.start_sec = time.tv_sec;
		data->time.start_usec = time.tv_usec;
	}
	return(data);
}