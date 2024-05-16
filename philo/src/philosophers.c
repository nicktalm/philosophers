/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/16 18:24:00 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	get_current_time(t_philo *philo)
{
	struct timeval	current;
	long			sec;
	int				ms;
	long			diff;

	gettimeofday(&current, NULL);
	sec = current.tv_sec - philo->start.tv_sec;
	ms = current.tv_usec - philo->start.tv_usec;
	if (ms < 0)
	{
		ms += 1000000;
		sec--;
	}
	diff = sec * 1000 + ms / 1000;
	return (diff);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	gettimeofday(&philo->start, NULL);
	if (philo->data->nb_philo % 2 == 0)
		usleep(10000);
	while (1)
	{
		printf("%d %d is thinking\n", get_current_time(philo), philo->id);
		if (!pthread_mutex_lock(&philo->forks) && !pthread_mutex_lock(&philo->next->forks))
		{
			printf("%d %d has taken a fork\n", get_current_time(philo), philo->id);
			printf("%d %d is eating\n", get_current_time(philo), philo->id);
			usleep(philo->data->time_eat);
		}
	}
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
		tmp = tmp->next;
		i++;
	}
	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(tmp->thread, NULL);
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
