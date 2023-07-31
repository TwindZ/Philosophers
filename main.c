/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/31 12:37:09 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_param(t_data *data)
{
	printf("nb_philo : %d\n", data->param.nb_philo);
	printf("ttd : %d\n", data->param.ttd);
	printf("tte :%d\n", data->param.tte);
	printf("tts :%d\n", data->param.tts);
	printf("nb_time :%d\n", data->param.nb_time);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*a;
	unsigned char	*temp;
	unsigned int	i;
	
	i = 0;
	a = malloc(count * size);
	if (!a)
		return (NULL);
	temp = (unsigned char *)a;
	while (i < (count * size))
		temp[i++] = '\0';
	return (a);
}

long int ft_max_min(long int nbr)
{
	if(nbr >= -2147483648 && nbr <= 2147483647)
		return(1);
	return(0)
}

int	build_base_param(t_data *data, char **argv)
{
	long int nbr;
	
	nbr = ft_atoi(argv[1]);
	if (ft_max_min(nbr))
		data->param.nb_philo = nbr;
	else
		return (-1);
	nbr = ft_atoi(argv[2]);
	if (ft_max_min(nbr))
		data->param.nb_philo = nbr;
	else
		return (-1);
	nbr = ft_atoi(argv[3]);
	if (ft_max_min(nbr))
		data->param.nb_philo = nbr;
	else
		return (-1);
	nbr = ft_atoi(argv[4]);
	if (ft_max_min(nbr))
		data->param.nb_philo = nbr;
	if (argv[5])
	{
		nbr = ft_atoi(argv[5]);
		if (ft_max_min(nbr))
			data->param.nb_time = nbr;
		else
			return(-1);
	}
}

t_data *ft_init_data(char **argv)
{
	static t_data *data;
	
	if(!data)
	{
		data = ft_calloc(1, sizeof(data));
		if(!data)
			return (NULL);
			build_base_param(data, argv);

	}
	return(data);
}


int	ft_parse_argv(char **argv)
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

int main(int argc, char **argv)
{
	t_data *data;
	
	if(argc < 5 || argc > 6)
	{
		printf("parameter error\n./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat(optional)]\n");
		return(1);
	}
	if(ft_parse_argv(argv) == 0)
	{
		printf("only positif numeric argument are used by philo\n");
		return(2);
	}
	data = ft_init_data(argv);
	if(!data)
		exit(-1);
	print_param(data);
}