/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/29 00:20:13 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_law			law;
	pthread_t		boss_thread;

	if (argc < 5 || argc > 6 || get_law(argc, argv, &law) || setup_philos(&law))
		return (1);
	gettimeofday(&law.begin, NULL);
	if (law.nb_philos == 1)
	{
		print_timestamp(&law.philos[0], law.begin, 1, GRAB);
		ft_usleep(law.time_die);
		print_timestamp(&law.philos[0], law.begin, 1, DEAD);
		return (free_setup(&law, law.nb_philos, 0), 1);
	}
	set_last_meal_time(&law);
	if (law.meals != 0)
	{
		pthread_create(&boss_thread, NULL, boss, &law);
		setoff_philos(&law);
		pthread_join(boss_thread, NULL);
		while (law.nb_philos)
		{
			pthread_join(law.philos[law.nb_philos - 1].thread, NULL);
			law.nb_philos--;
		}
	}
	return (free_setup(&law, law.nb_philos, 0), 0);
}

	// printf("seconds : %ld\nmicro seconds : %i\n\n",
	// 		law.begin.tv_sec, law.begin.tv_usec);
	// printf("seconds : %ld\nmicro seconds : %i\n\n",
	// 		law.philos[0].last_meal.tv_sec, law.philos[0].last_meal.tv_usec);
