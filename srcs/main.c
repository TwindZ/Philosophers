/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/03 16:13:40 by emlamoth         ###   ########.fr       */
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

void	*routine(void *philoptr)
{
	t_philo *philo;

	philo = (t_philo *)philoptr;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	printf("%d\n", philo->id);
	// pthread_mutex_unlock(&philo->left_fork);
	// pthread_mutex_unlock(&philo->right_fork);
	return (NULL);
}


// void	join_thread(t_data *data)
// {
// 	t_philo *temp;
	
// 	int i;
// 	temp = data->philo;
// 	i = data->param.nb_philo;
// 	while(--i)
// 	{
// 		pthread_join(temp->thread, NULL);
// 		temp = temp->right;
// 	}
// }

// void	ft_action()
// {
	
// }


int main(int argc, char **argv)
{
	t_data data;
	if(argc < 5 || argc > 6)		
		return(err_handler(ERRNBPARAM));
	if(digit_argv(argv) == 0)
		return(err_handler(ERRONLYNB));
	ft_init_data(&data, argv);
	ft_init_philo(&data, data.philo);
	print_param(&data);
	
	for(int i = 0; i < data.param.nb_philo; i++)
	{
		pthread_create(&data.thread[i], NULL, &routine, &data.philo[i]);
		sleep(2);
	// 	printf("*************************************************\n");
	// 	printf("philo #%d status : %d\n", data.philo[i].id, data.philo[i].dead);
	// 	printf("left fork :%p right fork : %p\n", &data.philo[i].left_fork, &data.philo[i].right_fork);
	}
		
	// join_thread(data);
	// while(1)
	// {
	// 	if(time_calc(data) % 500 == 0)
	// 		printf("%d\n", (time_calc(data)));
	// 	if(time_calc(data) % 1000 == 0)
	// 		printf("salut");
	// }
	return (0);
}