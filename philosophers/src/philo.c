/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:21:47 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 02:30:33 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_feeding_loop(t_philosopher *philo, int p);

void *routine(void *random_philo)
{
	t_philosopher	*philo;
	int	p;

	philo = (t_philosopher *)random_philo;
	if (philo->law->nb_philos % 2 == 0)
		p = 0;
	else
		p = 1;
	if (philo->meals_left && philo->position % 2 == 0)
	{
		if (think(philo, philo->law->time_eat))
			return (NULL);
		if (p)
			p++;
	}
	start_feeding_loop(philo, p);
	return (NULL);
}

static int	start_feeding_loop(t_philosopher *philo, int p)
{
	// printf("timestamp : %i\n", gettimestamp(philo->law->begin));
	while (philo->meals_left || philo->law->meals == -1)
	{
		if (philo->position == p && think(philo, philo->law->time_eat))
			return (printf("ISSUE : THINK\n"), 1);
		eat(philo);
		if (philo_sleep(philo))
			return (printf("ISSUE : SLEEP\n"), 1);
		if (philo->law->time_eat > philo->law->time_sleep \
			&& think(philo, philo->law->time_eat - philo->law->time_sleep))
			return (printf("ISSUE : THINK\n"), 1);
		if (p && p % 2 == 1 && p > philo->law->nb_philos)
			p = 1;
		else if (p && p % 2 == 0 && p > philo->law->nb_philos)
			p = 2;
		else if (p)
			p += 2;
		philo->meals_left--;
	}
	return (0);
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

void	print_timestamp(struct timeval starting_time, int position, enum state state)
{
	int	time_stamp;

	time_stamp = gettimestamp(starting_time);
	if (state == 0)
		printf("%i\t%i died\n", time_stamp, position);
	if (state == 1)
		printf("%i\t%i is eating\n", time_stamp, position);
	if (state == 2)
		printf("%i\t%i is thinking\n", time_stamp, position);
	if (state == 3)
		printf("%i\t%i is sleeping\n", time_stamp, position);
	if (state == 4)
		printf("%i\t%i has taken a fork\n", time_stamp, position);
}
