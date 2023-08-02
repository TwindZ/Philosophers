/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/02 17:10:48 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	time_calc(t_data *data)
{
	struct timeval time;
	int	count;
	
	count = 0;
	gettimeofday(&time, NULL);
	count = (((time.tv_usec - data->time.start_usec) / 1000)
			+ ((time.tv_sec - data->time.start_sec) * 1000));
	return (count);
	
}

void	*routine(void *dataptr)
{
	t_data *data;

	data = dataptr;
	write(1, "@\n", 2);
	pthread_mutex_lock(&data->main_lock);
	if(data->philo->id % 2 == 0)
		printf("paire");
	else
		printf("impaire");
	pthread_mutex_unlock(&data->main_lock);
	return (NULL);
}


void	join_thread(t_data *data)
{
	t_philo *temp;
	
	int i;
	temp = data->philo;
	i = data->param.nb_philo;
	while(--i)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->right;
	}
}

int main(int argc, char **argv)
{
	t_data *data;
	
	
	if(argc < 5 || argc > 6)		
		return(err_handler(ERRNBPARAM));
	if(digit_argv(argv) == 0)
		return(err_handler(ERRONLYNB));
	data = ft_init_data(argv);
	if(!data)
		return (-1);
	print_param(data);
	bigbang(data);
	int i = 0;
	
	while(i++ < data->param.nb_philo)
	{
		pthread_create(&data->philo->thread, NULL, &routine, NULL);
	}
	
	
	join_thread(data);
	// while(1)
	// {
	// 	if(time_calc(data) % 500 == 0)
	// 		printf("%d\n", (time_calc(data)));
	// 	if(time_calc(data) % 1000 == 0)
	// 		printf("salut");
	// }
	bigcrunch(data);
	return (0);
}