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

//check if the str are only numerical
int	checker_arg_chr(char *str)
{
	if (!str)
		return (1);
	while(*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

//check the argv and assign the nbr to the data params
int check_and_assigns_argv(char *argv[], t_data *data)
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