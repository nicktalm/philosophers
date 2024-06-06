/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:13:03 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/06 10:17:49 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

int	ft_mutex(t_philo *philo)
{
	int	value;

	value = 0;
	if (!pthread_mutex_lock(&philo->data->check_nbr_meal))
	{
		value = philo->nb_eat;
		pthread_mutex_unlock(&philo->data->check_nbr_meal);
	}
	return (value);
}

int	ft_mutex_2(t_philo *philo)
{
	int	value;

	value = 0;
	if (!pthread_mutex_lock(&philo->data->check))
	{
		value = philo->data->dead_philo;
		pthread_mutex_unlock(&philo->data->check);
	}
	return (value);
}

void	ft_usleep(unsigned int microseconds)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	elapsed = 0;
	if (gettimeofday(&start, NULL) == -1)
		return ;
	while (elapsed < microseconds)
	{
		if (gettimeofday(&current, NULL) == -1)
			return ;
		elapsed = (current.tv_sec - start.tv_sec) * 1000000;
		elapsed += (current.tv_usec - start.tv_usec);
		if (microseconds - elapsed > 1000)
			usleep(50);
	}
}

void	ft_message(int id, int i, t_philo *philo)
{
	long	time;

	time = 0;
	if (!pthread_mutex_lock(&philo->data->check_write))
	{
		time = ft_get_time(philo->data->start);
		if (ft_mutex_2(philo) == 0)
		{
			if (i == 0)
				printf("%ld %d has taken a fork\n", time, id);
			else if (i == 1)
				printf("%ld %d is eating\n", time, id);
			else if (i == 2)
			{
				printf("%ld %d is sleeping\n", time, id);
			}
			else if (i == 3)
				printf("%ld %d is thinking\n", time, id);
		}
		if (i == 4)
			printf("\033[1;31m%ld %d died\033[0m\n", time, id);
		pthread_mutex_unlock(&philo->data->check_write);
	}
}
