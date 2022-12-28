/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 15:10:46 by amorvai          ###   ########.fr       */
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
	set_last_meal_time(&law);
	if (law.meals != 0)
	{
		pthread_create(&boss_thread, NULL, boss, &law);
		setoff_philos(&law);
		pthread_join(boss_thread, NULL);
	}
	free_setup(&law, law.nb_philos, 0);
	return (0);
}

	// printf("seconds : %ld\nmicro seconds : %i\n\n",
	// 		law.begin.tv_sec, law.begin.tv_usec);
	// printf("seconds : %ld\nmicro seconds : %i\n\n",
	// 		law.philos[0].last_meal.tv_sec, law.philos[0].last_meal.tv_usec);
