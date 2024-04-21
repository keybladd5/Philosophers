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

//Take string and returns a pointer to the c character occurrence
static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*(char *)s && *(char *)s != (char)c)
		s++;
	if (*(char *)s != (char)c)
		return (0);
	return ((char *)s);
}

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
	while (*str && (ft_strchr("\n\t\v\f\r ", *str)) != NULL)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str && (ft_strchr("0123456789", *str)) != NULL)
	{
		output = (output * 10) + (*str - '0');
		str++;
	}
	return (output * sign);
}

