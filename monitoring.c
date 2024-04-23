/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:44:36 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/23 11:44:37 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_die_monitor(t_data *data)
{
	size_t limit;
	int i;

	i = 0;
	pthread_mutex_lock(&(data)->m_last_meal);
	limit = data->philo_arr[i].last_meal + data->time_die;
	pthread_mutex_unlock(&(data)->m_last_meal);
	while (i < data->n_philo)
	{
		if (ft_time_elapsed() > limit)
		{
			pthread_mutex_lock(&data->m_print);
			printf ("%zu %d", ft_time_elapsed(), data->philo_arr[i].nbr);
			printf (" has died\n");
			pthread_mutex_unlock(&data->m_print);
			pthread_mutex_lock(&(data)->m_dead);
			data->die_flag = 1;
			pthread_mutex_unlock(&(data)->m_dead);
			return (1);
		}
		i++;
	}
	return (0);
}
static int	ft_meals_monitor(t_data *data)
{
	int philos_ate;
	int i;

	i = 0;
	philos_ate = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&(data)->m_count_meals);
		if (data->philo_arr[i].count_meals < data->must_meals)
			philos_ate = 0;
		else
			philos_ate = 1;
		pthread_mutex_unlock(&(data)->m_count_meals);
		if (philos_ate == 0)
			return 	(0);
		i++;
	}
	return (1);
}

//MONITOR LOOP
int ft_monitoring(t_data *data)
{
	while (1)
		if (ft_die_monitor(data) || ft_meals_monitor(data))
			return (1);
	return (0);
}
