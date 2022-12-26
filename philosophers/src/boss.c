/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:27:13 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/26 23:34:19 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_dead() {
	
}

static void kill_all() {
	
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
						
void	*boss(void *law2)
{
	t_law	*law;

	law = (t_law *)law2;
	while (1)
	{
		usleep(1000);
		if (is_dead()) {
			kill_all();
		}	
		if (!is_anyone_hungry(law))
			break ;
	}
	return (NULL);
}