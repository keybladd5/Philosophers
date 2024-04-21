/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:10:07 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/21 17:10:09 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void rutina(t_philo *philo)
{
	//aqui deben comer
	//pensar
	//dormir
	printf("hola soy el filo %d\n", philo->nbr);
}

// Gets the current time in milliseconds
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);

	int i = 0;
	memset(&data, 0, sizeof(t_data));
	data.n_philo = ft_atoi(argv[1]);
	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	data.philo_arr = (t_philo *)malloc(sizeof(t_philo) * data.n_philo);
	while(i < data.n_philo)
	{
		data.philo_arr[i].nbr = i+1;
		pthread_create(&data.philo_arr[i].id, NULL, (void *)rutina, &data.philo_arr[i]);
		i++;
	}
	i = 0;
	while(i < data.n_philo)
	{
		pthread_join(data.philo_arr[i].id, NULL);
		i++;
	}
	free(data.philo_arr);
	return 1;	
}