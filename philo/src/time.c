/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:22:53 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/12 17:21:37 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	get_time_in_microseconds(struct timeval *time)
{
	return (time->tv_sec * 1000000 + time->tv_usec);
}

long	ft_get_time(struct timeval start_time)
{
	struct timeval	time_now;
	long			start_microseconds;
	long			current_microseconds;

	gettimeofday(&time_now, NULL);
	start_microseconds = get_time_in_microseconds(&start_time);
	current_microseconds = get_time_in_microseconds(&time_now);
	return ((current_microseconds - start_microseconds) / 1000);
}
