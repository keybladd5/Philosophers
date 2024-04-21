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
# include "colors.h"

typedef struct s_philo t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_meals;
	int				die_flag;
	size_t			start;
	pthread_mutex_t	m_print;
	pthread_mutex_t *spoon_arr;
	t_philo			*philo_arr;
}	t_data;

struct s_philo
{
	int			nbr;
	pthread_t	id;
	size_t		lats_meal;
	t_data		*data;
};


//Utils

int		ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);


#endif