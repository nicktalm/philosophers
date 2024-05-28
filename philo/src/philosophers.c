/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/28 17:02:19 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
			usleep(100);
	}
}

int	check_for_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo->now_death.tv_sec != 0)
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}

long	ft_get_time(struct timeval time)
{
	struct timeval	time_now;
	long			start_time;
	long			current_time;

	gettimeofday(&time_now, NULL);
	start_time = (time.tv_sec * 1000
			+ time.tv_usec / 1000);
	current_time = (time_now.tv_sec * 1000
			+ time_now.tv_usec / 1000);
	return ((current_time - start_time));
}

void	ft_message(long time, int id, int i, t_philo *philo)
{
	if (check_for_death(philo) == 0)
	{
		if (i == 0)
		{
			printf("%ld %d has taken a fork 🍽\n", time, id);
			printf("%ld %d has taken a fork 🍽\n", time, id);
			printf("%ld %d is eating 🍝\n", time, id);
			ft_usleep(philo->data->time_eat);
		}
		else if (i == 1)
		{
			printf("%ld %d is sleeping 😴\n", time, id);
			ft_usleep(philo->data->time_sleep);
		}
		else if (i == 2)
			printf("%ld %d is thinking 🤔\n", time, id);
	}
	if (i == 3)
		printf("\033[1;31m%ld %d died 💀\033[0m\n", time, id);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	gettimeofday(&philo->start, NULL);
	gettimeofday(&philo->last_meal, NULL);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while ((philo->nb_eat < philo->data->nb_eat_max || philo->data->nb_eat_max == -1) && check_for_death(philo) == 0)
	{
		ft_message(ft_get_time(philo->start), philo->id, 2, philo);
		if (philo->data->nb_philo == 1)
			return (NULL);
		if (pthread_mutex_lock(&philo->forks) == 0)
		{
			if (pthread_mutex_lock(&philo->next->forks) == 0)
			{
				ft_message(ft_get_time(philo->start), philo->id, 0, philo);
				// usleep(philo->data->time_eat);
				philo->nb_eat++;
				gettimeofday(&philo->last_meal, NULL);
				// printf("\033[1;31mnb_eat: %d id: %d\033[0m\n", philo->nb_eat, philo->id);
				// printf("last_meal: %ld\n", philo->last_meal.tv_sec);
				pthread_mutex_unlock(&philo->next->forks);
			}
			pthread_mutex_unlock(&philo->forks);
		}
		ft_message(ft_get_time(philo->start), philo->id, 1, philo);
		// usleep(philo->data->time_sleep);
	}
	// printf("id = %d\n", philo->id);
	return (NULL);
}

void	*monitoring_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while ((philo->nb_eat < philo->data->nb_eat_max || philo->data->nb_eat_max == -1) && check_for_death(philo) == 0)
	{
		if (philo->last_meal.tv_sec == 0)
			gettimeofday(&(philo)->last_meal, NULL);
		if (philo->data->time_die < ft_get_time(philo->last_meal))
		{
			if (!pthread_mutex_lock(&philo->data->dead) && check_for_death(philo) == 0)
			{
				gettimeofday(&philo->now_death, NULL);
				ft_message(ft_get_time(philo->start), philo->id, 3, philo);
			}
			pthread_mutex_unlock(&philo->data->dead);
			// printf("monitoring1 id = %d\n", philo->id);
			return (NULL);
		}
	}
	// printf("monitoring2 id = %d\n", philo->id);
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

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;
	int		i;
	int		nb_philo;

	i = 0;
	nb_philo = philo->data->nb_philo;
	tmp = philo;
	next = tmp->next;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&tmp->forks);
		pthread_mutex_destroy(&tmp->data->dead);
		free(tmp);
		tmp = next;
		next = tmp->next;
		i++;
	}
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
