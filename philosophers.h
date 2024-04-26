/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:10:28 by polmarti          #+#    #+#             */
/*   Updated: 2024/04/21 17:10:30 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include "colors.h"

// ERRORS
# define MALLOC_ERROR 1
# define ARGV_ERROR 2

//TYPES
# define EAT_INIT 3
# define TAKE_IN 4
# define TAKE_OFF 9
# define SPOON 5
# define DIED 6
# define THINK 7
# define SLEEP 8

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				n_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				must_meals;
	int				die_flag;
	size_t			start;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_count_meals;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	m_is_eating;
	pthread_mutex_t	*spoon_arr;
	t_philo			*philo_arr;
}	t_data;

struct s_philo
{
	int			nbr;
	int			count_meals;
	pthread_t	id;
	size_t		last_meal;
	int			is_eating;
	t_data		*data;
};

//Utils

int		ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_mutex(t_philo *philo, int type, int spoon);
size_t	ft_time_elapsed(void);

//Check_and_errors

void	ft_destroy_mutex(t_data *data, int n);
void	ft_destroy_pthreads(t_data *data, int n);
int		ft_safe_especific_mutex(t_data *data);
int		check_and_assigns_argv(char *argv[], t_data *data);
int		checker_arg_chr(char *str);

//Routine

void	routine(t_philo *philo);
void	ft_eat(t_philo *philo);

//Monitoring

void	ft_only_one_philo(void);
int		ft_monitoring(t_data *data);

//Main

void	ft_destroy_data(t_data *data);
int		ft_init_data_and_pthreads(t_data *data);

#endif