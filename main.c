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

//gcc main.c utils.c -pthread -g -fsanitize=thread -Werror -Wall -Wextra

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

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr - 1]);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu philo %d take an spoon %d\n",(get_current_time() - philo->data->start), philo->nbr, (philo->nbr - 1));
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->data->spoon_arr[philo->nbr]);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu philo %d take an spoon %d\n", (get_current_time() - philo->data->start), philo->nbr, philo->nbr);
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu philo %d eats\n", (get_current_time() - philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->m_print);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu philo %d finish eating\n", (get_current_time() - philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr - 1]);
	pthread_mutex_unlock(&philo->data->spoon_arr[philo->nbr]);
}
void rutina(t_philo *philo)
{
	ft_eat(philo);
	//pensar
	//dormir
}

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
	data.spoon_arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n_philo);
	pthread_mutex_init(&data.m_print, NULL);
	data.start = get_current_time();
	while(i < data.n_philo)
	{
		data.philo_arr[i].nbr = i+1;
		data.philo_arr[i].data = &data;
		pthread_mutex_init(&data.spoon_arr[i], NULL);
		pthread_create(&data.philo_arr[i].id, NULL, (void *)rutina, &data.philo_arr[i]);
		i++;
	}
	i = 0;
	while(i < data.n_philo)
	{
		pthread_join(data.philo_arr[i].id, NULL);
		pthread_mutex_destroy(&data.spoon_arr[i]);
		i++;
	}
	pthread_mutex_destroy(&data.m_print);
	free(data.philo_arr);
	return 1;	
}