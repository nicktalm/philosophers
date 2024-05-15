/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:39 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/15 17:39:26 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parsing(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments!\n"), 1);
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

int	main(int argc, char **argv)
{
	struct timeval	start;
	struct timeval	end;
	long			time_start;
	long			time_end;
	long			time_diff;

	parsing(argc, argv);
	gettimeofday(&start, NULL);
	usleep(200000);
	gettimeofday(&end, NULL);
	time_start = start.tv_sec * 1000 + start.tv_usec / 1000;
	time_end = end.tv_sec * 1000 + end.tv_usec / 1000;
	time_diff = time_end - time_start;
	printf("Start = %ld ms\n", time_start);
	printf("End   = %ld ms\n", time_end);
	printf("Diff  = %ld ms\n", time_diff);
	return (0);
}
