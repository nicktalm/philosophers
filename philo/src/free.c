/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:27:06 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/03 13:28:58 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;
	int		i;
	int		nb_philo;

	i = 0;
	nb_philo = philo->data->nb_philo;
	tmp = philo;
	pthread_mutex_destroy(&philo->data->check_write);
	pthread_mutex_destroy(&philo->data->check_death);
	pthread_mutex_destroy(&philo->data->check_meal);
	pthread_mutex_destroy(&philo->data->check_nbr_meal);
	pthread_mutex_destroy(&philo->data->check);
	while (i < nb_philo)
	{
		next = tmp->next;
		pthread_mutex_destroy(&tmp->forks);
		free(tmp);
		tmp = next;
		i++;
	}
}
