/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:24:47 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/07 15:54:20 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	perform_eating(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) == 0)
	{
		ft_message(philo->id, 0, philo);
		if (pthread_mutex_lock(second_fork) == 0)
		{
			ft_message(philo->id, 0, philo);
			ft_message(philo->id, 1, philo);
			ft_usleep(philo->data->time_eat);
			if (!pthread_mutex_lock(&philo->data->check_nbr_meal))
			{
				philo->nb_eat++;
				pthread_mutex_unlock(&philo->data->check_nbr_meal);
			}
			if (!pthread_mutex_lock(&philo->data->check_meal))
			{
				gettimeofday(&philo->last_meal, NULL);
				pthread_mutex_unlock(&philo->data->check_meal);
			}
			pthread_mutex_unlock(second_fork);
		}
		pthread_mutex_unlock(first_fork);
	}
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (!pthread_mutex_lock(&philo->data->check_meal))
	{
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&philo->data->check_meal);
	}
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while ((ft_mutex(philo) < philo->data->nb_eat_max
			|| philo->data->nb_eat_max == -1)
		&& ft_mutex_2(philo) == 0)
	{
		if (philo->data->nb_philo == 1)
			return (NULL);
		if (philo->id % 2 == 0)
			perform_eating(philo, &philo->forks, &philo->next->forks);
		else
			perform_eating(philo, &philo->next->forks, &philo->forks);
		ft_message(philo->id, 2, philo);
		ft_usleep(philo->data->time_sleep);
		ft_message(philo->id, 3, philo);
		ft_usleep(500);
	}
	return (NULL);
}

long	check_last_meal(t_philo *philo)
{
	long	value;

	value = 0;
	if (!pthread_mutex_lock(&philo->data->check_meal))
	{
		if (philo->last_meal.tv_sec == 0)
			gettimeofday(&(philo)->last_meal, NULL);
		value = ft_get_time(philo->last_meal);
		pthread_mutex_unlock(&philo->data->check_meal);
	}
	return (value);
}

void	*monitoring_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while ((ft_mutex(philo) < philo->data->nb_eat_max
			|| philo->data->nb_eat_max == -1)
		&& ft_mutex_2(philo) == 0)
	{
		if (philo->data->time_die <= check_last_meal(philo))
		{
			if (!pthread_mutex_lock(&philo->data->check_death)
				&& ft_mutex_2(philo) == 0)
			{
				if (!pthread_mutex_lock(&philo->data->check))
				{
					philo->data->dead_philo = 1;
					pthread_mutex_unlock(&philo->data->check);
				}
				ft_message(philo->id, 4, philo);
			}
			pthread_mutex_unlock(&philo->data->check_death);
			return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}

void	start_game(t_philo *philo, t_data *data)
{
	t_philo		*tmp;
	int			i;
	pthread_t	moni;

	tmp = philo;
	i = 0;
	gettimeofday(&philo->data->start, NULL);
	while (i < data->nb_philo)
	{
		pthread_create(&tmp->thread, NULL, routine, (void *)tmp);
		tmp = tmp->next;
		i++;
	}
	pthread_create(&moni, NULL, monitoring_thread, (void *)tmp);
	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	pthread_join(moni, NULL);
}
