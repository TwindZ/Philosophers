/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/08 10:22:00 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	time_calc(struct timeval start_time)
{
	struct timeval time;
	int	count;
	
	count = 0;
	gettimeofday(&time, NULL);
	count = (((time.tv_usec - start_time.tv_usec) / 1000)
			+ ((time.tv_sec - start_time.tv_sec) * 1000));
	return (count);
	
}

//  timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

void	*routine(void *philoptr)
{
	t_philo *philo;
	philo = (t_philo *)philoptr;
	int	meals;
	int	elapsed;
	int ready;
	int life;
	
	ready = 0;
	elapsed = 0;
	life = philo->ttd;
	meals = 0;
	if(((philo->id % 2)) == 0)
	{
		printf("%d %d is sleeping\n",
			time_calc(philo->time), philo->id);
		// if(life - philo->tts > 0)
			while(time_calc(philo->time) != philo->tts)
				usleep(1);
		// else
		// {
		// 	while(time_calc(philo->time) != life)
		// 	;
		// 	philo->dead = true;
		// }	
				
	}
	elapsed = time_calc(philo->time);
	while(1 && meals != philo->nb_time)
	{	
		ready = 1;
		while(ready)
		{
			if(!(pthread_mutex_lock(&philo->left_fork) == -1))
			{
				if(!(pthread_mutex_lock(philo->right_fork) == -1))
					ready = 0;
				else
					pthread_mutex_unlock(&philo->left_fork);
				// if((life - time_calc(philo->time) - elapsed) < 0)
				// 	philo->dead = true;
				// printf("%d - %d - %d = %d\n", life, time_calc(philo->time), elapsed, (life - time_calc(philo->time) - elapsed));
			}
			// if(time_calc(philo->time) - elapsed >)
		}
		printf("%d %d has taken a fork\n",
			time_calc(philo->time), philo->id);
		elapsed = time_calc(philo->time);
		printf("%d %d is eating\n",
			time_calc(philo->time), philo->id);
		while(1)
		{
			// if((time_calc(philo->time) - elapsed - philo->tte) < 0)
			// {
			// 	while(time_calc(philo->time) < elapsed + philo->tts)
			// 	;
			// 	philo->dead = true;
			// }
			if(time_calc(philo->time) == (philo->tte + elapsed))
			{
				pthread_mutex_unlock(&philo->left_fork);
				pthread_mutex_unlock(philo->right_fork);
				break ;
			}
		}
		elapsed = time_calc(philo->time);
		meals++;
		printf("%d %d is sleeping\n",
			time_calc(philo->time), philo->id);
		// while(1)
		// {
			// if((time_calc(philo->time) - elapsed) < 0)
			// {
				while(time_calc(philo->time) < elapsed + philo->tts)
				;
			// 	philo->dead = true;
			// }
			usleep(50);
		// }
		elapsed = time_calc(philo->time);
		printf("%d %d is thinking\n",
			time_calc(philo->time), philo->id);
		while(1)
		{
			if(time_calc(philo->time) == elapsed + philo->ttd)
			{
				break ;
			}
		}
		elapsed = time_calc(philo->time);
		life =  philo->ttd;
	}
	return (NULL);
}


int	join_thread(t_data *data)
{
	int i;

	i = 0;
	while(i < data->param.nb_philo)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	// int i;
	
	if(argc < 5 || argc > 6)		
		return(err_handler(ERRNBPARAM));
	if(digit_argv(argv) == 0)
		return(err_handler(ERRONLYNB));
	ft_init_data(&data, argv);
	ft_init_philo(&data, data.philo);
	print_param(&data);
	gettimeofday(&data.time, NULL);
	for(int i = 0; i < data.param.nb_philo; i++)
	{
		gettimeofday(&data.philo[i].time, NULL);
		pthread_create(&data.thread[i], NULL, &routine, &data.philo[i]);
		// sleep(2);
		// printf("*************************************************\n");
		// printf("philo #%d status : %d\n", data.philo[i].id, data.philo[i].dead);
		// printf("left fork :%p right fork : %p\n", &data.philo[i].left_fork, data.philo[i].right_fork);
	}

	
	// while(1)
	// {
	// 	i = 0;
	// 	while(&data.philo[i])
	// 	{
	// 		if(data.philo[i].dead == true)
	// 			printf("%d %d dead\n",
	// 		time_calc(data.time), data.philo[i].id);
	// 		i++;
	// 		usleep(200);
	// 	}
	// }
	
	join_thread(&data);
	
	//**//**//** destroy thread **//**//**//
	
	
	// while(1)
	// {
	// 	if(time_calc(time) % 500 == 0)
	// 		printf("%d\n", time_calc(time));
	// 	if(time_calc(time) % 1000 == 0)
	// 		printf("salut");
	// }
	return (0);
}