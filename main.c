/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:33:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/08/01 16:37:59 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->right = NULL;
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
			last = ft_lstlast(*philo);
			last->right = new_philo;
		}
	}
}

void	ft_freenull(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}


int err_handler(char *msg)
{
	printf("%s", msg);
	return (-1);
}


void	print_param(t_data *data)
{
	printf("nb_philo : %d\n", data->param.nb_philo);
	printf("ttd : %d\n", data->param.ttd);
	printf("tte :%d\n", data->param.tte);
	printf("tts :%d\n", data->param.tts);
	printf("nb_time :%d\n", data->param.nb_time);
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

long int ft_max_min(long int nbr)
{
	if(nbr >= -2147483648 && nbr <= 2147483647)
		return(1);
	return(0);
}

void	check_max_param(int *param, char *arg)
{
	long int nbr;
	
	nbr = ft_atoi(arg);
	if (ft_max_min(nbr))
		*param = nbr;
	else
		*param = -1;
}

int	build_base_param(t_data *data, char **argv)
{
	check_max_param(&data->param.nb_philo, argv[1]);
	check_max_param(&data->param.ttd, argv[2]);
	check_max_param(&data->param.tte, argv[3]);
	check_max_param(&data->param.tts, argv[4]);
	check_max_param(&data->param.nb_time, argv[5]);
	if (data->param.nb_philo == -1 || data->param.ttd == -1 
			|| data->param.tte == -1 || data->param.tts == -1 
			|| data->param.nb_time == -1)
			return (err_handler(ERRMAXVAL));
	return (0);
}

t_data *ft_init_data(char **argv)
{
	static t_data *data;
	
	if(!data)
	{
		data = ft_calloc(1, sizeof(data));
		if(!data)
			return (NULL);
		if(build_base_param(data, argv) == -1)
		{
			free(data);
			return (NULL);
		}	
	}
	return(data);
}

int	digit_argv(char **argv)
{
	int i;
	int j;

	i = 1;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if(ft_isdigit(argv[i][j]) == 0)
				return(0);
			j++;
		}
		i++;
	}
	return (1);
}
void	time_calc(t_data *data, struct timeval time)
{
	gettimeofday(&time, NULL);
	data->time.count_usec = (((time.tv_usec - data->time.start_usec) / 1000) + ((time.tv_sec - data->time.start_sec) * 1000));
	usleep(1);
}

// void	*routine()
// {
// 	printf("salut\n");
// 	return(NULL);
// }

// void create_thread(t_data *data)
// {
// 	int size;

// 	size = data->param.nb_philo;
// 	data->thread = ft_calloc(data->param.nb_philo + 1, sizeof(pthread_t *));
// 	while(size > 0)
// 	{
// 		data->thread[size] = ft_calloc(1, sizeof(pthread_t));
// 		pthread_create(&data->thread[size], NULL, &routine, NULL);
// 		size--;
// 	}
// }

// void	join_thread(t_data *data)
// {
// 	int size;

// 	size = data->param.nb_philo;
// 	while(size > 0)
// 	{
// 		pthread_join(data->thread[size], NULL);
// 		size--;
// 	}
// }

void	create_philo(t_data *data)
{
	int size;

	size = data->param.nb_philo;
	
}

int main(int argc, char **argv)
{
	t_data *data;
	// struct timeval time;
	
	if(argc < 5 || argc > 6)		
		return(err_handler(ERRNBPARAM));
	if(digit_argv(argv) == 0)
		return(err_handler(ERRONLYNB));
	data = ft_init_data(argv);
	if(!data)
		return (-1);
	print_param(data);
	

	// if(gettimeofday(&time, NULL) == -1)
	// 	return (-1);
	// data->time.start_sec = time.tv_sec;
	// data->time.start_usec = time.tv_usec;
	// while(1)
	// {
	// 	time_calc(data, time);
	// 	printf("%ld\n", data->time.count_usec);
	// }
	
	return (0);
}