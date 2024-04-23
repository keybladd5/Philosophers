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

//to debug
void	debug(t_philo *philo)
{
	size_t current_time;

	pthread_mutex_lock(&philo->data->m_print);
	current_time = get_current_time() - philo->data->start;
	printf ("%zu ", current_time);
	printf("hola soy el filo ");
	printf(UBLUE);
	printf("%d\n", philo->nbr);
	printf(RESET);
	pthread_mutex_unlock(&philo->data->m_print);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->die_flag)
	{	
		/*pthread_mutex_lock(&philo->data->m_print);
		elapsed_time = get_current_time() - philo->data->start;
		printf("tiempo de actual %zu\n", elapsed_time);
		printf("tiempo de last_meal %zu\n", philo->last_meal);
		printf("resultado : %zu ", elapsed_time - philo->last_meal);
		printf("tiempo para morir %zu\n", philo->data->time_die);
		printf("%d ", philo->nbr);
		printf("filo muerto\n");
		pthread_mutex_unlock(&philo->data->m_print);*/
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}
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
	data.start = ft_time_elapsed();
	while(i < data.n_philo)
	{
		data.philo_arr[i].nbr = i+1;// El primer philo es l nbr i+1 = 0+1 = 1
		data.philo_arr[i].data = &data;
		data.philo_arr[i].count_meals = 0;
		data.philo_arr[i].last_meal = 0;
		pthread_mutex_init(&data.spoon_arr[i], NULL);
		pthread_create(&data.philo_arr[i].id, NULL, (void *)routine, &data.philo_arr[i]);
		i++;
	}
	//MONITOR LOOP
	if (ft_monitoring(&data))
	{
		i = 0;
		while(i < data.n_philo)
		{
			pthread_join(data.philo_arr[i].id, NULL);
			pthread_mutex_destroy(&data.spoon_arr[i]);
			i++;
		}
		pthread_mutex_destroy(&data.m_print);
		pthread_mutex_destroy(&data.m_dead);
		pthread_mutex_destroy(&data.m_last_meal);
		pthread_mutex_destroy(&data.m_count_meals);
		free(data.spoon_arr);
		free(data.philo_arr);
	}
	return 1;	
}
