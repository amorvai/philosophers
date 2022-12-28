/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 02:34:48 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_law			law;
	pthread_t		boss_thread;

	if (argc < 5 || argc > 6 || get_law(argc, argv, &law) || setup_philos(&law))
		return (1);
	gettimeofday(&law.begin, NULL);
	printf("seconds : %ld\nmicro seconds : %i\n\n", \
			law.begin.tv_sec, law.begin.tv_usec);
	// printf("timestamp : %i\n", gettimestamp(law.begin));
	if (law.meals != 0)
	{
		pthread_create(&boss_thread, NULL, boss, &law);
		setoff_philos(&law);
	}
	if (law.meals > 0)
		ft_usleep(law.time_die * law.meals);
	else
		while (1)
			;
	return (0);
}
