/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:12:55 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/21 18:12:58 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Gets the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

//Convert a string to an integer
int	ft_atoi(const char *str)
{
	int output;
	int	sign;

	output = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'\
	 || *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		output = (output * 10) + (*str - '0');
		str++;
	}
	return (output * sign);
}

//take the mutex to print to protect the action, print the current time
//and print a message based on type var
void	print_mutex(t_philo *philo, int type, int spoon)
{
	//pendiente añadir una protecion para no printear si el philo que llama a esta funcion esta muerto
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->die_flag)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_print);
	printf(ICYAN);
	printf("%zu miliseconds ▻ ", ft_time_elapsed());
	printf(RESET);
	if (type != SPOON)
		(void)spoon;
	if (type == EAT_INIT)
		printf("philo %d eats\n", philo->nbr);
	else if (type == EAT_END)
		printf("philo %d finish eating\n", philo->nbr);
	else if (type == SPOON)
		printf("philo %d take the spoon %d\n", philo->nbr, spoon);
	else if (type == THINK)
		printf("philo %d is thinking\n", philo->nbr);
	else if (type == SLEEP)
		printf("philo %d is sleeping\n", philo->nbr);
	pthread_mutex_unlock(&philo->data->m_print);
}

size_t	ft_time_elapsed(void)
{
	static size_t start = 0;

	if (start == 0)
		start = get_current_time();
	return (get_current_time() -  start);
}
