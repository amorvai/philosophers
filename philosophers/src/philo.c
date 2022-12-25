/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:21:47 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/25 22:56:24 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	try(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	philo_sleep(t_philosopher *philo);
void	think(t_philosopher *philo);
void	print_timestamp(struct timeval starting_time, int position, enum state state);

void *routine(void *random_philo)
{
	t_philosopher	*philo;
	
	philo = (t_philosopher *)random_philo;
	try(philo);
	return (NULL);
}

static void	try(t_philosopher *philo)
{
	int	p;
	
	if (philo->law->nb_philos % 2 == 0)
		p = 0;
	else
		p = 1;
	// printf("timestamp : %i\n", gettimestamp(philo->law->begin));
	if (philo->position % 2 == 0)
		think(philo);
	while (philo->meals_left && p == 0)
	{
		eat(philo);
		philo_sleep(philo);
		philo->meals_left--;
		// printf("Hi, I am #%i, and I am alive. (Please let me die)\n", philo->position);
	}
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_timestamp(philo->law->begin, philo->position, 4);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_timestamp(philo->law->begin, philo->position, 4);
	print_timestamp(philo->law->begin, philo->position, 1);
	gettimeofday(&philo->last_meal, NULL);
	ft_usleep(philo->law->time_eat);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

void	philo_sleep(t_philosopher *philo)
{
	print_timestamp(philo->law->begin, philo->position, 3);
	ft_usleep(philo->law->time_sleep);
}

void	think(t_philosopher *philo)
{
	print_timestamp(philo->law->begin, philo->position, 2);
	ft_usleep(philo->law->time_eat);
	
}

void	print_timestamp(struct timeval starting_time, int position, enum state state)
{
	printf("%i\t", gettimestamp(starting_time));
	printf("%i ", position);
	if (state == 0)
		printf("died\n");
	if (state == 1)
		printf("is eating\n");
	if (state == 2)
		printf("is thinking\n");
	if (state == 3)
		printf("is sleeping\n");
	if (state == 4)
		printf("has taken a fork\n");
}