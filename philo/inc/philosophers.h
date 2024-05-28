/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:33 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/28 16:28:11 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	struct s_philo	*philo;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat_max;
	pthread_mutex_t	dead;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_t		monitoring_thread;
	struct timeval	start;
	struct timeval	last_meal;
	struct timeval	now_death;
	pthread_mutex_t	forks;
	int				nb_eat;
	struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

// philosophers.c

int		main(int argc, char **argv);

// init_parsing.c

void	init_data(t_data *data, char **argv);
t_philo	*create_philo(int id, t_data *data);
t_philo	*init_philo(t_data *data);
int		parsing(int argc, char **argv);

// utils.c

int		ft_atoi(const char *str);

#endif