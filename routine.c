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
	print_mutex(philo, SLEEP);
	ft_usleep(philo->data->time_sleep);
}
void	ft_think(t_philo *philo)
{
	print_mutex(philo, THINK);

}
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr - 1]);
	print_mutex(philo, SPOON);
	pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr]);
	print_mutex(philo, SPOON2);
	print_mutex(philo, EAT_INIT);
	ft_usleep(philo->data->time_eat);
	print_mutex(philo, EAT_END);
	philo->last_meal = (get_current_time() - philo->data->start);
	philo->count_meals++;
	pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr - 1]);
	pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr]);
}

void	routine(t_philo *philo)
{
	while(!dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}