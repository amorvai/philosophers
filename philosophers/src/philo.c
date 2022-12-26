/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:21:47 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/26 23:22:11 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	try(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	philo_sleep(t_philosopher *philo);
void	think(t_philosopher *philo, int	milliseconds);
int		will_i_die(t_philosopher *philo, int var);
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
	{
		think(philo, philo->law->time_eat);
		if (p)
			p++;
	}
	while (philo->meals_left)
	{
		if (philo->position == p)
			think(philo, philo->law->time_eat);
		eat(philo);
		philo_sleep(philo);
		if (philo->law->time_eat > philo->law->time_sleep)
			think(philo, philo->law->time_eat - philo->law->time_sleep);
		if (p && p % 2 == 1 && p >= philo->law->nb_philos)
			p = 1;
		else if (p && p % 2 == 0 && p >= philo->law->nb_philos)
			p = 2;
		else if (p)
			p += 2;
		philo->meals_left--;
	}
}
	
	// while (philo->meals_left && p == 0)
	// {
	// 	eat(philo);
	// 	philo_sleep(philo);
	// 	philo->meals_left--;
	// 	// printf("Hi, I am #%i, and I am alive. (Please let me die)\n", philo->position);
	// }
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
	will_i_die(philo, philo->law->time_sleep);
	print_timestamp(philo->law->begin, philo->position, 3);
	ft_usleep(philo->law->time_sleep);
}

void	think(t_philosopher *philo, int	milliseconds)
{
	will_i_die(philo, milliseconds);
	print_timestamp(philo->law->begin, philo->position, 2);
	ft_usleep(milliseconds);
}

int		will_i_die(t_philosopher *philo, int var)
{
	if (gettimestamp(philo->last_meal) + var > philo->law->time_die)
	{
		ft_usleep(philo->law->time_die - gettimestamp(philo->last_meal));
		print_timestamp(philo->law->begin, philo->position, DEAD);
		return (1);
	}
	return (0);
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