/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:55:42 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/31 11:38:17 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libc.h>

typedef struct s_param
{
	int	nb_philo;
	int	ttd;
	int	tts;
	int	tte;
	int	nb_time;
}				t_param;

typedef struct s_data
{
	t_param	param;
}				t_data;

long int	ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif