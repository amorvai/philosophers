/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:31 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 00:45:44 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	set_law(int argc, char **argv, t_law *law)
{
	if (ft_atoi(argv[1], &law->nb_philos) || law->nb_philos <= 0)
		return (1);
	if (ft_atoi(argv[2], &law->time_die) || law->time_die < 0)
		return (1);
	if (ft_atoi(argv[3], &law->time_eat) || law->time_eat < 0)
		return (1);
	if (ft_atoi(argv[4], &law->time_sleep) || law->time_sleep < 0)
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &law->meals) || law->meals <= 0)
			return (1);
	}
	else
		law->meals = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_law			law;

	if (argc < 5 || argc > 6 || set_law(argc, argv, &law))
		return (1);
	if (set_table(&law))
		return (1);
	return (0);
}
