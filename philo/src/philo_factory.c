/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:30:32 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 01:05:30 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	set_up_philos2(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		law->philos[i].law = law;
		law->philos[i].position = i + 1;
		law->philos[i].state = THINK;
		law->philos[i].meals_left = law->meals;
		if (pthread_mutex_init(&law->forks[i].mutex, NULL))
			return (free_setup(law, i, 0), 1);
		if (pthread_mutex_init(&law->philos[i].meals_mutex, NULL))
			return (free_setup(law, i, 1), 1);
		if (pthread_mutex_init(&law->philos[i].termination_mutex, NULL))
			return (free_setup(law, i, 2), 1);
		law->philos[i].r_fork = &law->forks[i];
		if (i >= 1)
			law->philos[i - 1].l_fork = &law->forks[i];
		i++;
	}
	law->philos[i - 1].l_fork = &law->forks[0];
	return (0);
}

int	set_up_philos(t_law *law)
{
	law->philos = ft_calloc(law->nb_philos, sizeof(t_philosopher));
	if (!law->philos)
		return (1);
	law->forks = ft_calloc(law->nb_philos, sizeof(t_fork));
	if (!law->forks)
		return (free(law->philos), 1);
	if (pthread_mutex_init(&law->printf_mutex, NULL))
		return (free(law->philos), free(law->forks), 1);
	if (set_up_philos2(law))
		return (1);
	return (0);
}

void	set_last_meal_time(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		law->philos[i].last_meal = law->begin;
		i++;
	}
}

int	set_off_philos(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		if (pthread_create(&law->philos[i].thread,
				NULL, routine, &law->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_setup(t_law *law, int i, int y)
{
	int	j;

	j = 0;
	pthread_mutex_destroy(&law->printf_mutex);
	while (j < i)
	{
		pthread_mutex_destroy(&law->forks[j].mutex);
		pthread_mutex_destroy(&law->philos[j].meals_mutex);
		pthread_mutex_destroy(&law->philos[j].termination_mutex);
		j++;
	}
	if (y >= 1)
		pthread_mutex_destroy(&law->forks[j].mutex);
	if (y == 2)
		pthread_mutex_destroy(&law->philos[j].meals_mutex);
	free(law->philos);
	free(law->forks);
}

// void	print_philo(t_law *law)
// {
	// int i;
	// i = 0;
	// while (i < law->nb_philos)
	// {
	// 	printf("philo nb %i: r_fork: %i, l_fork: %i\n", law->philos[i].position,
	// law->philos[i].r_fork->position, law->philos[i].l_fork->position);
	// 	i++;
	// }
// }
