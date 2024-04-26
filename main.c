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

void	ft_destroy_data(t_data *data)
{
	ft_destroy_pthreads(data, data->n_philo);
	ft_destroy_mutex(data, data->n_philo);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_last_meal);
	pthread_mutex_destroy(&data->m_count_meals);
	pthread_mutex_destroy(&data->m_is_eating);
	free(data->spoon_arr);
	free(data->philo_arr);
}

// El primer philo es l nbr i+1 = 0+1 = 1
int	ft_init_data_and_pthreads(t_data *data)
{
	int	i;

	i = 0;
	if (ft_safe_especific_mutex(data))
		return (1);
	data->start = ft_time_elapsed();
	while (i < data->n_philo)
	{
		data->philo_arr[i].nbr = i + 1;
		data->philo_arr[i].data = data;
		data->philo_arr[i].count_meals = 0;
		data->philo_arr[i].last_meal = 0;
		data->philo_arr[i].is_eating = 0;
		if (pthread_mutex_init(&data->spoon_arr[i], NULL))
			return (ft_destroy_mutex(data, (i - 1)), 1);
		if (pthread_create(&data->philo_arr[i].id, NULL, \
		(void *)routine, &data->philo_arr[i]))
			return (ft_destroy_pthreads(data, i - 1), 1);
		i++;
	}
	return (0);
}

//TO-DO: Checker arguments and protect pthread funcs 
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (check_and_assigns_argv(argv, &data))
		return (ARGV_ERROR);
	data.philo_arr = (t_philo *)malloc(sizeof(t_philo) * data.n_philo);
	if (!data.philo_arr)
		return (MALLOC_ERROR);
	data.spoon_arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data.n_philo);
	if (!data.spoon_arr)
		return (free(data.philo_arr), MALLOC_ERROR);
	if (data.n_philo == 1)
		return (ft_only_one_philo(), free(data.philo_arr), \
		free(data.spoon_arr), 1);
	if (ft_init_data_and_pthreads(&data))
		return (free(data.philo_arr), free(data.spoon_arr), 1);
	if (ft_monitoring(&data))
		ft_destroy_data(&data);
	return (0);
}
