/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 10:56:46 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_lock);
		if(philo->left_fork.locked == false)
		{
			if(philo->right_fork->locked == false)
			{
				philo->left_fork.locked = true;
				philo->right_fork->locked = true;
				pthread_mutex_unlock(philo->fork_lock);
				pthread_mutex_lock(&philo->left_fork.fork);
				pthread_mutex_lock(&philo->right_fork->fork);
				mutex_print(philo, FORK);
				mutex_print(philo, FORK);
				return(true);
			}
		}
		pthread_mutex_unlock(philo->fork_lock);
		return (false);	
	
}

void	drop_fork(t_philo *philo)
{
		pthread_mutex_lock(philo->fork_lock);
		philo->left_fork.locked = false;
		philo->right_fork->locked = false;
		pthread_mutex_unlock(&philo->left_fork.fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(philo->fork_lock);
}

int main(int argc, char **argv)
{
	t_data data;
	
	if(argc < 5 || argc > 6)		
		return(err_handler(ERRNBPARAM));
	if(digit_argv(argv) == 0)
		return(err_handler(ERRONLYNB));
	if(!ft_init_data(&data, argv))
		return (-1);
	ft_init_philo(&data, data.philo);
	print_param(&data);
	process_start(&data);
	join_thread(&data);
	clean_mutex(&data);
	
	return (0);
}
