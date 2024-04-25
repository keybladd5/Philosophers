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

//TO-DO: Checker arguments and protect pthread funcs 
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	int i = 0;
	memset(&data, 0, sizeof(t_data));
	if (check_and_assigns_argv(argv, &data))
		return (ARGV_ERROR);
	data.philo_arr = (t_philo *)malloc(sizeof(t_philo) * data.n_philo);
	if (!data.philo_arr)
		return (MALLOC_ERROR);
	data.spoon_arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n_philo);
	if (!data.spoon_arr)
		return (free(data.philo_arr), MALLOC_ERROR);	
	pthread_mutex_init(&data.m_print, NULL);
	pthread_mutex_init(&data.m_dead, NULL);
	pthread_mutex_init(&data.m_last_meal, NULL);
	pthread_mutex_init(&data.m_count_meals, NULL);
	pthread_mutex_init(&data.m_is_eating, NULL);
	data.start = ft_time_elapsed();
	while(i < data.n_philo)
	{
		data.philo_arr[i].nbr = i+1;// El primer philo es l nbr i+1 = 0+1 = 1
		data.philo_arr[i].data = &data;
		data.philo_arr[i].count_meals = 0;
		data.philo_arr[i].last_meal = 0;
		data.philo_arr[i].is_eating = 0;
		pthread_mutex_init(&data.spoon_arr[i], NULL);
		pthread_create(&data.philo_arr[i].id, NULL, (void *)routine, &data.philo_arr[i]);
		i++;
	}
	//MONITOR LOOP
	if (ft_monitoring(&data))
	{
		i = 0;
		printf("termino el programa en %zu\n", ft_time_elapsed());
		while(i < data.n_philo)
		{
			pthread_join(data.philo_arr[i].id, NULL);
			pthread_mutex_destroy(&data.spoon_arr[i]);
			i++;
		}
		printf("se terminaron de unir los threads en %zu\n", ft_time_elapsed());
		pthread_mutex_destroy(&data.m_print);
		pthread_mutex_destroy(&data.m_dead);
		pthread_mutex_destroy(&data.m_last_meal);
		pthread_mutex_destroy(&data.m_count_meals);
		pthread_mutex_destroy(&data.m_is_eating);
		free(data.spoon_arr);
		free(data.philo_arr);
	}
	return 1;	
}
