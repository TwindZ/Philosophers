/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   univers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:57:58 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/02 17:09:01 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo()
{
	t_philo	*philo;
	static int id;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	pthread_mutex_init(&philo->fork, NULL);
	philo->id = ++id;
	philo->right = NULL;
	return (philo);
}

t_philo	*last_philo(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while (philo->right != NULL)
		philo = philo->right;
	return (philo);
}

void	add_philo(t_philo **philo, t_philo *new_philo)
{
	t_philo	*last;

	if (philo)
	{
		if (*philo == NULL)
			*philo = new_philo;
		else
		{
			last = last_philo(*philo);
			last->right = new_philo;
		}
	}
}

void	bigbang(t_data *data)
{
	int i;
	t_philo *last;
	
	i = 0;
	while(i++ < data->param.nb_philo)
		add_philo(&data->philo, new_philo());
	last = last_philo(data->philo);
	last->right = data->philo;
}

void	bigcrunch(t_data *data)
{
	t_philo *temp;
	
	while(data->param.nb_philo--)
	{
		temp = data->philo->right;
		pthread_mutex_destroy(&data->philo->fork);
		free(data->philo);
		data->philo = NULL;
		data->philo = temp;
	}
	data->philo = NULL;
	free(data);
}