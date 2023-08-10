/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/10 14:37:49 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_calc(struct timeval start_time)
{
	struct timeval time;//slow ?
	int	count;
	
	count = 0;
	gettimeofday(&time, NULL);
	count = (((time.tv_usec - start_time.tv_usec) / 1000)
			+ ((time.tv_sec - start_time.tv_sec) * 1000));
	return (count);
	
}

bool	mutex_dead(t_philo *philo, int opt)
{
	bool	status;
	
	status = false;
	pthread_mutex_lock(philo->dead_lock);
	if(opt)
	{
		*philo->dead = true;
		mutex_print(philo, DEAD, 1);
	}
	else
		status = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return(status);
}

void	mutex_print(t_philo *philo, char *msg, int opt)
{
	pthread_mutex_lock(philo->print_lock);
	if(mutex_dead(philo, 0) == false)
		printf("%d %d %s", time_calc(philo->time), philo->id, msg);
	else if(opt)
	{
		printf("%d %d %s", time_calc(philo->time), philo->id, msg);
	}
	pthread_mutex_unlock(philo->print_lock);
	
}
bool	take_fork(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_lock);
		if(philo->left_fork.locked == false)
		{
			if(philo->right_fork->locked == false)
			{
				philo->left_fork.locked = true;
				pthread_mutex_lock(&philo->left_fork.fork);
				mutex_print(philo, FORK, 0);
				philo->right_fork->locked = true;
				pthread_mutex_lock(&philo->right_fork->fork);
				mutex_print(philo, FORK, 0);
				return(true);
			}
		}
		pthread_mutex_unlock(philo->fork_lock);
		return (false);	
	
}

void	drop_fork(t_philo *philo)
{
		pthread_mutex_unlock(&philo->left_fork.fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		philo->left_fork.locked = false;
		philo->right_fork->locked = false;
}

void	*routine(void *philoptr)
{
	t_philo *philo;
	philo = (t_philo *)philoptr;
	int	meals;
	int	elapsed;

	elapsed = 0;
	meals = 0;
	if(((philo->id & 1) == 1))
	{
		mutex_print(philo, THINK, 0);
		while(1)
		{
			if((time_calc(philo->time) - elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
				return (NULL);
			}
			if(time_calc(philo->time) == philo->tte)
				break ;
			usleep(40);
		}
	}
	while(1)
	{	
		//-------fork---------------------------------------
		while(mutex_dead(philo, 0) == false)
		{
			if((time_calc(philo->time) - elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
				return (NULL);
			}
			if(take_fork(philo) == true)
				break;
			usleep(40);
			
		}
		mutex_print(philo, EAT, 0);
		//---------eat---------------------------------------
		elapsed = time_calc(philo->time);
		while(mutex_dead(philo, 0) == false)
		{
			if((time_calc(philo->time) - elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
					drop_fork(philo);
				return (NULL);
			}
			if((time_calc(philo->time) - elapsed) == (philo->tte))
			{
				drop_fork(philo);
				break ;
			}
			usleep(40);
		}
		if(mutex_dead(philo, 0) == true)
			return (NULL);
		mutex_print(philo, SLEEP, 0);
		//-----sleep-----------------------------------------------
		while(mutex_dead(philo, 0) == false)
		{
			// printf("%d - %d = %d > %d\n", time_calc(philo->time), elapsed, (time_calc(philo->time) - elapsed), life);
			if((time_calc(philo->time) - elapsed) == (philo->ttd))
			{
				if(mutex_dead(philo, 0) == false)
					mutex_dead(philo, 1);
				return (NULL);
			}
			if((time_calc(philo->time) - elapsed) == (philo->tte + philo->tts))
				break ;
			usleep(40);
		}	
		if(mutex_dead(philo, 0) == true)
			return (NULL);
		//------ think ----------------------------------------------
		mutex_print(philo, THINK, 0);
		usleep(200);
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
		pthread_mutex_lock(&data.dead_lock);
		if(data.dead == true)
		{
			write(1, "test\n", 5);
			pthread_mutex_unlock(&data.dead_lock);
			// pthread_mutex_unlock(&data.print_lock);
			break;
		}	
		pthread_mutex_unlock(&data.dead_lock);
			
		usleep(50);
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
