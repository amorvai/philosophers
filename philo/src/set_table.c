/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:26:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 00:55:41 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lonely_philo(t_law *law)
{
	print_timestamp(&law->philos[0], law->begin, 1, GRAB);
	ft_usleep(law->time_die);
	law->philos[0].state = DEAD;
	print_timestamp(&law->philos[0], law->begin, 1, DEAD);
	free_setup(law, law->nb_philos, 0);
}

void	reel_threads_in(t_law *law)
{
	int	i;

	i = 0;
	while (i < law->nb_philos)
	{
		pthread_join(law->philos[i].thread, NULL);
		i++;
	}
}

int	set_table(t_law *law)
{
	pthread_t		boss_thread;

	if (set_up_philos(law))
		return (1);
	gettimeofday(&law->begin, NULL);
	set_last_meal_time(law);
	if (law->nb_philos == 1)
	{
		lonely_philo(law);
		return (1);
	}
	if (pthread_create(&boss_thread, NULL, boss, law))
		return (1);
	if (set_off_philos(law))
		return (1);
	pthread_join(boss_thread, NULL);
	reel_threads_in(law);
	free_setup(law, law->nb_philos, 0);
	return (0);
}
