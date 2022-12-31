/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:21:47 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 00:48:26 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	feeding_loop(t_philosopher *philo, int p)
{
	while (philo->meals_left != 0)
	{
		if (philo->position == p && p++ && \
			philo_think(philo, philo->law->time_eat))
			return (1);
		if (philo_eat(philo))
			return (1);
		if (philo_sleep(philo))
			return (1);
		if (philo->law->time_eat > philo->law->time_sleep && \
			philo_think(philo, philo->law->time_eat - philo->law->time_sleep))
			return (1);
		if (p && p % 2 == 1 && p >= philo->law->nb_philos)
			p = 1;
		else if (p && p % 2 == 0 && p >= philo->law->nb_philos)
			p = 2;
		else if (p)
			p += 2;
		pthread_mutex_lock(&philo->meals_mutex);
		philo->meals_left--;
		pthread_mutex_unlock(&philo->meals_mutex);
	}
	return (0);
}

void	*routine(void *random_philo)
{
	t_philosopher	*philo;
	int				p;

	philo = (t_philosopher *)random_philo;
	if (philo->law->nb_philos % 2 == 0)
		p = 0;
	else
		p = 1;
	if (philo->position == p)
		print_timestamp(philo, philo->law->begin, philo->position, THINK);
	if (philo->meals_left && philo->position % 2 == 0)
	{
		print_timestamp(philo, philo->law->begin, philo->position, THINK);
		if (philo_think(philo, philo->law->time_eat))
			return (NULL);
		if (p)
			p++;
	}
	feeding_loop(philo, p);
	return (NULL);
}
