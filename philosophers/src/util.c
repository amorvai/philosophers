/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:22:22 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/26 22:38:42 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "philo.h"

void	ft_usleep(int millisecs)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	if (millisecs > 5)
		usleep((millisecs - 5) * 1000);
	while (gettimestamp(begin) < millisecs)
		;
}

int	gettimestamp(struct timeval starting_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\nmicro seconds : %i\n\n", \
	// 		current_time.tv_sec, current_time.tv_usec);
	return (1000 * (current_time.tv_sec - starting_time.tv_sec) \
			+ 0.001 * (current_time.tv_usec - starting_time.tv_usec));
}

int	gettimestamp_mod(struct timeval starting_time, struct timeval current_time)
{
	return (1000 * (current_time.tv_sec - starting_time.tv_sec) \
			+ 0.001 * (current_time.tv_usec - starting_time.tv_usec));
}
