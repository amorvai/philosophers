/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:34:39 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/30 23:05:21 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	print_timestamp(philo, philo->law->begin, philo->position, EAT);
	gettimeofday(&philo->last_meal, NULL);
	if (will_i_die(philo, philo->law->time_eat))
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (1);
	}
	ft_usleep(philo->law->time_eat);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	return (0);
}

static int	eat_even(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	print_timestamp(philo, philo->law->begin, philo->position, EAT);
	gettimeofday(&philo->last_meal, NULL);
	if (will_i_die(philo, philo->law->time_eat))
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return (1);
	}
	ft_usleep(philo->law->time_eat);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	return (0);
}

int	philo_eat(t_philosopher *philo)
{
	philo->state = EAT;
	if (philo->position % 2)
	{
		if (eat_odd(philo))
			return (1);
	}
	else
	{
		if (eat_even(philo))
			return (1);
	}
	if (check_death_row(philo))
		return (1);
	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	philo->state = SLEEP;
	print_timestamp(philo, philo->law->begin, philo->position, SLEEP);
	if (will_i_die(philo, philo->law->time_sleep))
		return (1);
	ft_usleep(philo->law->time_sleep);
	if (check_death_row(philo))
		return (1);
	philo->state = THINK;
	print_timestamp(philo, philo->law->begin, philo->position, THINK);
	return (0);
}

int	philo_think(t_philosopher *philo, int milliseconds)
{
	if (will_i_die(philo, milliseconds))
		return (1);
	ft_usleep(milliseconds);
	if (check_death_row(philo))
		return (1);
	return (0);
}
