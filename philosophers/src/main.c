/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/26 23:28:08 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_anyone_hungry(t_law *law);
int		loop(t_law *law);
void	*boss(void *law2);
int		boss_loop(t_law *law);

int	main(int argc, char **argv)
{
	t_law			law;
	pthread_t		boss_thread;

	if (argc < 5 || argc > 6 || get_law(argc, argv, &law) || init_philos(&law))
		return (1);
	gettimeofday(&law.begin, NULL);
	printf("seconds : %ld\nmicro seconds : %i\n\n", \
			law.begin.tv_sec, law.begin.tv_usec);
	// printf("timestamp : %i\n", gettimestamp(law.begin));
	pthread_create(&boss_thread, NULL, boss, &law);
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


