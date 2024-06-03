/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/03 15:40:52 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_mutex_2(t_philo *philo);

// long	ft_get_time(struct timeval time)
// {
// 	struct timeval	time_now;
// 	long			start_time;
// 	long			current_time;

// 	if (time.tv_sec == 0)
// 		gettimeofday(&time, NULL);
// 	gettimeofday(&time_now, NULL);
// 	start_time = (time.tv_sec * 1000000 + time.tv_usec);
// 	current_time = (time_now.tv_sec * 1000000 + time_now.tv_usec);
// 	return (current_time / 1000 - start_time / 1000);
// }

long	get_time_in_milliseconds(struct timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

long	ft_get_time(struct timeval start_time)
{
	struct timeval	time_now;
	long			start_milliseconds;
	long			current_milliseconds;

	gettimeofday(&time_now, NULL);
	start_milliseconds = get_time_in_milliseconds(&start_time);
	current_milliseconds = get_time_in_milliseconds(&time_now);
	return (current_milliseconds - start_milliseconds);
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
		ft_usleep(100);
	while ((ft_mutex(philo) < philo->data->nb_eat_max || philo->data->nb_eat_max == -1) && ft_mutex_2(philo) == 0)
	{
		ft_message(philo->id, 3, philo);
		if (philo->data->nb_philo == 1)
			return (NULL);
		if (pthread_mutex_lock(&philo->forks) == 0)
		{
			if (pthread_mutex_lock(&philo->next->forks) == 0)
			{
				ft_message(philo->id, 0, philo);
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
				pthread_mutex_unlock(&philo->next->forks);
			}
			pthread_mutex_unlock(&philo->forks);
		}
		ft_usleep(philo->data->time_sleep);
		ft_message(philo->id, 2, philo);
	}
	return (NULL);
}

void	*monitoring_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while ((ft_mutex(philo) < philo->data->nb_eat_max || philo->data->nb_eat_max == -1) && ft_mutex_2(philo) == 0)
	{
		if (philo->last_meal.tv_sec == 0)
			gettimeofday(&(philo)->last_meal, NULL);
		if (philo->data->time_die < ft_get_time(philo->last_meal))
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (parsing(argc, argv))
		return (1);
	init_data(&data, argv);
	philo = init_philo(&data);
	start_game(philo, &data);
	free_philo(philo);
	return (0);
}
