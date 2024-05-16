/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/16 13:27:52 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (parsing(argc, argv))
		return (1);
	init_data(&data, argv);
	data.philo = init_philo(&data);
	philo = data.philo;
	int i = 0;
	while (i < philo->data->nb_philo)
	{
		printf("Philosopher ID: %d\n", philo->id);
		printf("Number of times philosopher has eaten: %d\n", philo->nb_eat);
		printf("Number of philosophers: %d\n", philo->data->nb_philo);
		printf("Time to die: %d\n", philo->data->time_die);
		printf("Time to eat: %d\n", philo->data->time_eat);
		printf("Time to sleep: %d\n", philo->data->time_sleep);
		printf("Max number of times to eat: %d\n\n\n", philo->data->nb_eat_max);
		philo = philo->next;
		i++;
	}
	return (0);
}
