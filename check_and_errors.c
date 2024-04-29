/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:22:58 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/22 14:23:00 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Destroy an array of mutex n times
void	ft_destroy_mutex(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->spoon_arr[i]);
		i++;
	}
}

//Join an array of pthreads n times
void	ft_destroy_pthreads(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(data->philo_arr[i].id, NULL);
		i++;
	}
}

//Init the specific mutex and check if some func fails to destroy the others
int	ft_safe_especific_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (pthread_mutex_destroy(&data->m_print), 1);
	if (pthread_mutex_init(&data->m_last_meal, NULL))
		return (pthread_mutex_destroy(&data->m_print), \
		pthread_mutex_destroy(&data->m_dead), 1);
	if (pthread_mutex_init(&data->m_count_meals, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		pthread_mutex_destroy(&data->m_dead);
		pthread_mutex_destroy(&data->m_last_meal);
		return (1);
	}
	if (pthread_mutex_init(&data->m_is_eating, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		pthread_mutex_destroy(&data->m_dead);
		pthread_mutex_destroy(&data->m_last_meal);
		pthread_mutex_destroy(&data->m_count_meals);
		return (1);
	}
	return (0);
}

//check if the str are only numerical
int	checker_arg_chr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9' || i > 10)
			return (1);
		str++;
		i++;
	}
	return (0);
}

//check the argv and assign the nbr to the data params
int	check_and_assigns_argv(char *argv[], t_data *data)
{
	if (checker_arg_chr(argv[1]) || checker_arg_chr(argv[2]) || \
	checker_arg_chr(argv[3]) || checker_arg_chr(argv[4]))
		return (ARGV_ERROR);
	if (argv[5] && checker_arg_chr(argv[5]))
		return (ARGV_ERROR);
	else if ((argv[5] && !checker_arg_chr(argv[5])))
		data->must_meals = ft_atoi(argv[5]);
	else
		data->must_meals = INT_MAX;
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (data->n_philo <= 0 || data->time_die <= 0 || \
	data->time_eat <= 0 || data->time_sleep <= 0)
		return (ARGV_ERROR);
	return (0);
}
