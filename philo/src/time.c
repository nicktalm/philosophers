/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:22:53 by ntalmon           #+#    #+#             */
/*   Updated: 2024/06/07 16:03:43 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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

// long	get_time_in_milliseconds(struct timeval *time)
// {
// 	return (time->tv_sec * 1000 + time->tv_usec / 1000);
// }

// long	ft_get_time(struct timeval start_time)
// {
// 	struct timeval	time_now;
// 	long			start_milliseconds;
// 	long			current_milliseconds;

// 	gettimeofday(&time_now, NULL);
// 	start_milliseconds = get_time_in_milliseconds(&start_time);
// 	current_milliseconds = get_time_in_milliseconds(&time_now);
// 	return (current_milliseconds - start_milliseconds);
// }


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
