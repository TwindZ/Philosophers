/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/08 17:30:45 by emlamoth         ###   ########.fr       */
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

bool	mutex_meals(int opt)
{
	t_data	*data;
	bool	status;
	
	status = false;
	data = struct_data(NULL);
	pthread_mutex_lock(&data->meals_lock);
	if(opt)
		data->meals++;
	else
		if(data->meals >= data->param.nb_time * data->param.nb_philo)
			status = true;
		else
			status = false;
	pthread_mutex_unlock(&data->meals_lock);
	return(status);
}

bool	mutex_dead(int opt)
{
	t_data	*data;
	bool	status;
	
	status = false;
	data = struct_data(NULL);
	pthread_mutex_lock(&data->dead_lock);
	if(opt)
		data->dead = true;
	else
		status = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return(status);
}

void	mutex_print(int time, int philo_id, char *msg)
{
	t_data *data;
	
	data = struct_data(NULL);
	if(!mutex_dead(0))
	{
		pthread_mutex_lock(&data->print_lock);
		printf("%d %d %s", time, philo_id, msg);
		pthread_mutex_unlock(&data->print_lock);
	}
	
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
		mutex_print(time_calc(philo->time), philo->id, "is thinking\n");
		while(1)
		{
			if(time_calc(philo->time) >= philo->tte)
				break;
			// usleep(100);
		}
	}
	elapsed = time_calc(philo->time);
	while(1 && meals != philo->nb_time)
	{	
		pthread_mutex_lock(&philo->left_fork);
		mutex_print(time_calc(philo->time), philo->id, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		mutex_print(time_calc(philo->time), philo->id, "has taken a fork\n");
		mutex_print(time_calc(philo->time), philo->id, "is eating\n");
		life -= time_calc(philo->time);
		while(mutex_dead(0) == false)
		{
			if(life < time_calc(philo->time) - elapsed - philo->tts)
				mutex_dead(1);
			// printf("%d\n", philo->tts);
			if(time_calc(philo->time) >= (philo->tte + elapsed))
			{
				pthread_mutex_unlock(&philo->left_fork);
				pthread_mutex_unlock(philo->right_fork);
				break ;
			}
			// usleep(100);
		}
		if(mutex_dead(0) == true)
			return (NULL);
		life = philo->ttd;
		mutex_meals(1);
		mutex_print(time_calc(philo->time), philo->id, "is sleeping\n");
		while(mutex_dead(0) == false)
		{
			if(life < time_calc(philo->time) - elapsed)
				mutex_dead(1);
			// printf("%d < %d - %d %d\n", life, time_calc(philo->time), elapsed, (time_calc(philo->time) - elapsed ));
			if(time_calc(philo->time) < elapsed + philo->tts)
				break ;
			// usleep(100);
		}
		if(mutex_dead(0) == true)
			return (NULL);
		life -= time_calc(philo->time);
		mutex_print(time_calc(philo->time), philo->id, "is thinking\n");
		elapsed = time_calc(philo->time);
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

	
	while(1)
	{
		if(mutex_dead(0) == true)
			mutex_print(0, 0, "test");
	}
	
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
