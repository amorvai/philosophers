/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:34:39 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 04:43:28 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	eat_odd(t_philosopher *philo)
{
	sem_wait(philo->law->forks);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	sem_wait(philo->law->forks);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	print_timestamp(philo, philo->law->begin, philo->position, EAT);
	gettimeofday(&philo->last_meal, NULL);
	if (will_i_die(philo, philo->law->time_eat))
	{
		sem_post(philo->law->forks);
		sem_post(philo->law->forks);
		return (1);
	}
	ft_usleep(philo->law->time_eat);
	sem_post(philo->law->forks);
	sem_post(philo->law->forks);
	return (0);
}

static int	eat_even(t_philosopher *philo)
{
	sem_wait(philo->law->forks);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	sem_wait(philo->law->forks);
	print_timestamp(philo, philo->law->begin, philo->position, GRAB);
	print_timestamp(philo, philo->law->begin, philo->position, EAT);
	gettimeofday(&philo->last_meal, NULL);
	if (will_i_die(philo, philo->law->time_eat))
	{
		sem_post(philo->law->forks);
		sem_post(philo->law->forks);
		return (1);
	}
	ft_usleep(philo->law->time_eat);
	sem_post(philo->law->forks);
	sem_post(philo->law->forks);
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
	if (sem_open("/finish", 0) != SEM_FAILED)
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
	if (sem_open("/finish", 0) != SEM_FAILED)
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
	if (sem_open("/finish", 0) != SEM_FAILED)
		return (1);
	return (0);
}
