/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:34:39 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 00:42:37 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo)
{
	philo->state = EAT;
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_timestamp(philo->law->begin, philo->position, GRAB);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_timestamp(philo->law->begin, philo->position, GRAB);
	print_timestamp(philo->law->begin, philo->position, EAT);
	gettimeofday(&philo->last_meal, NULL);
	ft_usleep(philo->law->time_eat);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

int	philo_sleep(t_philosopher *philo)
{
	print_timestamp(philo->law->begin, philo->position, SLEEP);
	if (will_i_die(philo, philo->law->time_sleep))
		return (1);
	philo->state = SLEEP;
	ft_usleep(philo->law->time_sleep);
	return (0);
}

int	think(t_philosopher *philo, int	milliseconds)
{
	print_timestamp(philo->law->begin, philo->position, THINK);
	if (will_i_die(philo, milliseconds))
		return (1);
	philo->state = THINK;
	ft_usleep(milliseconds);
	return (0);
}

int		will_i_die(t_philosopher *philo, int var)
{
	if (gettimestamp(philo->last_meal) + var > philo->law->time_die)
	{
		ft_usleep(philo->law->time_die - gettimestamp(philo->last_meal));
		philo->state = DEAD;	
		print_timestamp(philo->law->begin, philo->position, DEAD);
		pthread_mutex_lock(&philo->termination_mutex);
		philo->die_now_bitch = 1;
		pthread_mutex_unlock(&philo->termination_mutex);
		return (1);
	}
	return (0);
}
