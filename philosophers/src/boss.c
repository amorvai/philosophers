/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:27:13 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 02:27:00 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_law *law)
{
	int i;

	i = 0;
	while (i < law->nb_philos)
	{
		pthread_mutex_lock(&law->philos[i].termination_mutex);
		if (law->philos[i].die_now_bitch == 1)
		{
			pthread_mutex_unlock(&law->philos[i].termination_mutex);
			return (1);
		}
		pthread_mutex_unlock(&law->philos[i].termination_mutex);
		i++;
	}
	return (0);
}

// static void	tell_them_to_die(t_philosopher *philo)
// {
// 	pthread_mutex_lock(&philo->termination_mutex);
// 	philo->die_now_bitch = 1;
// 	pthread_mutex_unlock(&philo->termination_mutex);
// }

static void	kill_all(t_law *law)
{
	int i;

	i = 0;
	while (i < law->nb_philos)
	{
		// tell_them_to_die(&law->philos[i]);
		pthread_mutex_lock(&law->philos[i].termination_mutex);
		law->philos[i].die_now_bitch = 1;
		pthread_mutex_unlock(&law->philos[i].termination_mutex);
		i++;
	}
}

int	is_anyone_hungry(t_law *law)
{
	int	i;

	i = 0;
	if (law->meals == -1)
		return (1);
	// if (law->meals == 0)  // shouldnt be possible, no threads should be created
	// 	return (0);
	while (i < law->nb_philos)
	{
		if (law->philos[i].meals_left > 0)
			return (1);
		i++;
	}
	return (0);
}

void	*boss(void *law2)
{
	t_law	*law;

	law = (t_law *)law2;
	while (1)
	{
		usleep(1000);
		if (is_dead(law))
		{
			kill_all(law);
			break ;
		}	
		if (!is_anyone_hungry(law))
			break ;
	}
	return (NULL);
}