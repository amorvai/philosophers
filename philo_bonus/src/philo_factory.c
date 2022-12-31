/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:30:32 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 04:49:11 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_philo(t_philosopher *philo, int i, t_law *law)
{
	philo->position = i + 1;
	philo->state = THINK;
	philo->meals_left = law->meals;
	philo->last_meal = law->begin;
	philo->law = law;
}

static void	wait_for_philos(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

static int	set_up_philos(t_law *law)
{
	t_philosopher	philo;
	int				i;
	pid_t			id;

	law->printf_sem = sem_open("/print", O_CREAT, 0644, 1);
	law->forks = sem_open("/forks", O_CREAT, 0644, law->nb_philos);
	sem_unlink("/print");
	sem_unlink("/forks");
	i = 0;
	while (i < law->nb_philos)
	{
		id = fork();
		if (id == 0)
		{
			init_philo(&philo, i, law);
			if (routine(&philo))
				return (1);
			return (0);
		}
		if (id != -1)
			i++;
	}
	if (id != 0)
		wait_for_philos(law);
	return (sem_unlink("/finish"), 0);
}

int	set_table(t_law *law)
{
	gettimeofday(&law->begin, NULL);
	if (law->nb_philos == 1)
	{
		printf("%i\t1 has taken a fork\n", gettimestamp(law->begin));
		ft_usleep(law->time_die);
		printf("%i\t1 died\n", gettimestamp(law->begin));
		return (1);
	}
	if (set_up_philos(law))
		return (1);
	return (0);
}
