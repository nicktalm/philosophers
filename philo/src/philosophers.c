/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/17 12:15:55 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	get_current_time(t_philo *philo)
{
	struct timeval	current_time;
	long			start_time_in_mics;
	long			current_time_in_mics;

	gettimeofday(&current_time, NULL);
	start_time_in_mics = (philo->start.tv_sec * 1000
			+ philo->start.tv_usec / 1000);
	current_time_in_mics = (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000);
	return ((current_time_in_mics - start_time_in_mics));
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	gettimeofday(&philo->start, NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->nb_eat < philo->data->nb_eat_max || philo->data->nb_eat_max == -1 )
	{
		printf("%ld %d is thinking 🤔\n", get_current_time(philo), philo->id);
		if (pthread_mutex_lock(&philo->forks) == 0)
		{
			if (pthread_mutex_lock(&philo->next->forks) == 0)
			{
				printf("%ld %d has taken a fork 🍽\n", get_current_time(philo), philo->id);
				printf("%ld %d is eating 🍝\n", get_current_time(philo), philo->id);
				usleep(philo->data->time_eat);
				philo->nb_eat++;
				gettimeofday(&philo->last_meal, NULL);
				printf("\033[1;31mnb_eat: %d id: %d\033[0m\n", philo->nb_eat, philo->id);
				// printf("last_meal: %ld\n", philo->last_meal.tv_sec);
				pthread_mutex_unlock(&philo->next->forks);
			}
			pthread_mutex_unlock(&philo->forks);
		}
		printf("%ld %d is sleeping 😴\n", get_current_time(philo), philo->id);
		usleep(philo->data->time_sleep);
	}
	return (NULL);
}

void	*monitoring_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	return (NULL);
}

void	start_game(t_philo *philo, t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&tmp->thread, NULL, &routine, (void *)tmp);
		pthread_create(&tmp->monitoring_thread, NULL, &monitoring_thread, (void *)tmp);
		tmp = tmp->next;
		i++;
	}
	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(tmp->thread, NULL);
		pthread_join(tmp->monitoring_thread, NULL);
		tmp = tmp->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	if (parsing(argc, argv))
		return (1);
	init_data(&data, argv);
	philo = init_philo(&data);
	start_game(philo, &data);
	return (0);
}
