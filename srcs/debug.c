/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:07:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/02 14:08:08 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_param(t_data *data)
{
	printf("nb_philo : %d\n", data->param.nb_philo);
	printf("ttd : %d\n", data->param.ttd);
	printf("tte :%d\n", data->param.tte);
	printf("tts :%d\n", data->param.tts);
	printf("nb_time :%d\n", data->param.nb_time);
}