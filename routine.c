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

/*Mutex the two spoons, if the last philosopher calls this function,
take the spoon 0 as the right spoon.
Print with mutex the spoon taken.*/
void	spoon_handler(t_philo *philo, int mode)
{
	if (mode == TAKE_IN)
	{
		pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr - 1]);
		if (philo->nbr == philo->data->n_philo)
			pthread_mutex_lock(&philo->data->spoon_arr[0]);
		else
			pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr]);
		print_mutex(philo, SPOON, philo->nbr - 1);
		if (philo->nbr == philo->data->n_philo)
			print_mutex(philo, SPOON, 0);
		else
			print_mutex(philo, SPOON, philo->nbr);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr - 1]);
		if (philo->nbr == philo->data->n_philo)
			pthread_mutex_unlock(&philo->data->spoon_arr[0]);
		else
			pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr]);
	}
}

/*Print with mutex the "sleep" message, and call the own function 
to wait a milliseconds time.*/
void	ft_sleep(t_philo *philo)
{
	print_mutex(philo, SLEEP, 0);
	ft_usleep(philo->data->time_sleep);
}

//Print with mutex the "think" message.
void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->die_flag)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	print_mutex(philo, THINK, 0);
}

/* Print with mutex the "eat" message,
   and set the last meal time with mutex.
   Activate the is_eating flag with mutex,
   and deactivate it with mutex.
   Call ft_usleep to wait in milliseconds for the time_to_eat,
   and iterate the philo->count_meals variable with mutex. */
void	ft_eat(t_philo *philo)
{
	spoon_handler(philo, TAKE_IN);
	print_mutex(philo, EAT_INIT, 0);
	pthread_mutex_lock(&philo->data->m_last_meal);
	philo->last_meal = ft_time_elapsed();
	pthread_mutex_unlock(&philo->data->m_last_meal);
	pthread_mutex_lock(&philo->data->m_is_eating);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->m_is_eating);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_lock(&philo->data->m_count_meals);
	philo->count_meals++;
	pthread_mutex_unlock(&philo->data->m_count_meals);
	pthread_mutex_lock(&philo->data->m_is_eating);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->m_is_eating);
	spoon_handler(philo, TAKE_OFF);
}

/*The main routine executed by a philosopher thread.
 It controls the behavior of the philosopher, 
 including eating, sleeping, and thinking actions,
 until the philosopher has reached the required number of meals.
 If the philosopher's number is even, it waits for the eating_time
 for introducing a desynchronization in the multi-threaded work.
 It is important to note that access to the count_meals 
 variable is not protected since it is modified 
 only in the thread itself.. The local die_flag is updated 
 in each iteration of the loop, with mutex protection.
 The while loop will continue execution until the philosopher 
 reaches the required meals or the die_flag is true.*/
void	routine(t_philo *philo)
{
	int	die_flag;

	if (philo->nbr % 2 == 0)
		ft_usleep(philo->data->time_eat);
	while (philo->count_meals < philo->data->must_meals)
	{
		pthread_mutex_lock(&philo->data->m_dead);
		die_flag = philo->data->die_flag;
		pthread_mutex_unlock(&philo->data->m_dead);
		if (die_flag)
			return ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}
