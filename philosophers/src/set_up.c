/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:30:32 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 00:26:10 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// printf("before\n");
	// printf("after\n");

int	get_law(int argc, char **argv, t_law *law)
{
	if (ft_atoi(argv[1], &law->nb_philos) || law->nb_philos < 0)
		return (1);
	if (ft_atoi(argv[2], &law->time_die) || law->time_die < 0)
		return (1);
	if (ft_atoi(argv[3], &law->time_eat) || law->time_eat < 0)
		return (1);
	if (ft_atoi(argv[4], &law->time_sleep) || law->time_sleep < 0)
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &law->meals) || law->meals < 0)
			return (1);
	}
	else
		law->meals = -1;
	return (0);
}

void	free_failed_setup(t_law *law, int i, int y)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&law->forks[j].mutex);
		pthread_mutex_destroy(&law->philos[j].termination_mutex);
		j++;
	}
	if (y == 1)
		pthread_mutex_destroy(&law->forks[j].mutex);
	free(law->philos);
	free(law->forks);
}

int	setup_philos(t_law *law)
{
	int	i;

	i = 0;
	law->philos = ft_calloc(law->nb_philos, sizeof(t_philosopher));
	if (!law->philos)
		return (1);
	law->forks = ft_calloc(law->nb_philos, sizeof(t_fork));
	if (!law->forks)
		return (free(law->philos), 1);
	while (i < law->nb_philos)
	{
		law->philos[i].law = law;
		law->philos[i].position = i + 1;
		law->philos[i].state = THINK;
		law->philos[i].meals_left = law->meals;
		// law->forks[i].position = i;
		if (pthread_mutex_init(&law->forks[i].mutex, NULL))
			return (free_failed_setup(law, i, 0), 1);
		if (pthread_mutex_init(&law->philos[i].termination_mutex, NULL))
			return (free_failed_setup(law, i, 1), 1);
		law->philos[i].r_fork = &law->forks[i];
		if (i >= 1)
			law->philos[i - 1].l_fork = &law->forks[i];
		i++;
	}
	law->philos[i - 1].l_fork = &law->forks[0];
	return (0);
}

int	setoff_philos(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		pthread_create(&law->philos[i].thread, NULL, routine, &law->philos[i]);
		usleep(1);
		i++;
	}
	return (0);
}

// void	print_philo(t_law *law)
// {
	// int i;
	// i = 0;
	// while (i < law->nb_philos)
	// {
	// 	printf("philo nb %i: r_fork: %i, l_fork: %i\n", law->philos[i].position, law->philos[i].r_fork->position, law->philos[i].l_fork->position);
	// 	i++;
	// }
// }
