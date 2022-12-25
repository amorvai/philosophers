/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/25 22:57:03 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_anyone_hungry(t_law *law);
int	loop(t_law *law);

int	main(int argc, char **argv)
{
	t_law			law;

	if (argc < 5 || argc > 6 || get_law(argc, argv, &law) || init_philos(&law))
		return (1);
	gettimeofday(&law.begin, NULL);
	printf("seconds : %ld\nmicro seconds : %i\n\n", \
			law.begin.tv_sec, law.begin.tv_usec);
	// printf("timestamp : %i\n", gettimestamp(law.begin));
	if (is_anyone_hungry(&law))
	{
		loop(&law);
	}
	ft_usleep(law.time_die * law.meals);
	return (0);
}

int	loop(t_law *law)
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

int	is_anyone_hungry(t_law *law)
{
	int	i;

	i = 0;
	if (law->meals == -1)
		return (1);
	if (law->meals == 0)
		return (0);
	while (i < law->nb_philos)
	{
		if (law->philos[i].meals_left > 0)
			return (i + 1);
		i++;
	}
	return (0);
}

