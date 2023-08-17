/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:07:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/17 10:32:45 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_param(t_data *data)
{
	printf("nb_philo : %d\n", data->param.nb_philo);
	printf("ttd : %ld\n", data->param.ttd);
	printf("tte :%ld\n", data->param.tte);
	printf("tts :%ld\n", data->param.tts);
	printf("nb_time :%d\n", data->param.nb_time);
}
