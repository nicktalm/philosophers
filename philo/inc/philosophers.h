/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:33 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/12 17:20:38 by ntalmon          ###   ########.fr       */
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
	int				dead_philo;
	pthread_mutex_t	check_write;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_meal;
	pthread_mutex_t	check_nbr_meal;
	pthread_mutex_t	check;
	struct timeval	start;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_t		monitoring;
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
int		ft_mutex(t_philo *philo);
int		ft_mutex_2(t_philo *philo);
void	ft_usleep(unsigned int microseconds);
void	ft_message(int id, int i, t_philo *philo);

// free.c

void	free_philo(t_philo *philo);

// time.c

long	get_time_in_milliseconds(struct timeval *time);
long	ft_get_time(struct timeval start_time);

// routine.c

void	perform_eating(t_philo *philo, pthread_mutex_t *fork_1,
			pthread_mutex_t *fork_2, int i);
void	*routine(void *tmp);
long	check_last_meal(t_philo *philo);
void	*monitoring_thread(void *tmp);
void	start_game(t_philo *philo, t_data *data);

#endif