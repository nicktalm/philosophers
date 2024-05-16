/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:12:32 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/16 13:40:59 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		data->nb_eat_max = ft_atoi(argv[5]);
	else
		data->nb_eat_max = -1;
	data->philo = init_philo(data);
}

t_philo	*create_philo(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf("Error: malloc failed!\n"), NULL);
	philo->id = id;
	philo->nb_eat = 0;
	philo->data = data;
	philo->next = NULL;
	return (philo);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*first;
	t_philo	*tmp;
	int		i;

	first = create_philo(1, data);
	if (!first)
		return (NULL);
	tmp = first;
	i = 2;
	while (i <= data->nb_philo)
	{
		tmp->next = create_philo(i, data);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	tmp->next = first;
	return (first);
}

int	parsing(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments!\n"), 1);
	if (ft_atoi(argv[1]) < 1)
		return (printf("Error: number of philos must be greater than 0!\n"), 1);
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Error: argument %d is wrong!\n", i), 1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
