/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/16 17:13:51 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
