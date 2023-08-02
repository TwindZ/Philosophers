/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:54:21 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/02 14:46:57 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_freenull(void **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}


int err_handler(char *msg)
{
	printf("%s", msg);
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*a;
	unsigned char	*temp;
	unsigned int	i;
	
	i = 0;
	a = malloc(count * size);
	if (!a)
		return (NULL);
	temp = (unsigned char *)a;
	while (i < (count * size))
		temp[i++] = '\0';
	return (a);
}