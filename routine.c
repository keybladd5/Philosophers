/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:18:53 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/22 14:18:55 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	print_mutex(philo, SLEEP, 0);
	ft_usleep(philo->data->time_sleep);
}
void	ft_think(t_philo *philo)
{
	print_mutex(philo, THINK, 0);
}
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr - 1]);
	print_mutex(philo, SPOON, philo->nbr - 1);
	if (philo->nbr == philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->data->spoon_arr[0]);
		print_mutex(philo, SPOON, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr]);
		print_mutex(philo, SPOON, philo->nbr);
	}
	print_mutex(philo, EAT_INIT, 0);
	philo->last_meal = (get_current_time() - philo->data->start); //hay q obtener el tiempo antes de comer
	philo->count_meals++;
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr - 1]);
	if (philo->nbr == philo->data->n_philo)
		pthread_mutex_unlock(&philo->data->spoon_arr[0]);
	else
		pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr]);
	
}

void	routine(t_philo *philo)
{
	if (philo->nbr % 2 == 0)
		ft_usleep(philo->data->time_eat / 2);
	while(!philo->data->die_flag)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	
}