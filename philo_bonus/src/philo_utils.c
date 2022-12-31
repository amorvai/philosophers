/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 23:04:43 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 04:43:01 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	gettimestamp(struct timeval starting_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (1000 * (current_time.tv_sec - starting_time.tv_sec) \
			+ 0.001 * (current_time.tv_usec - starting_time.tv_usec));
}

// printf("seconds : %ld\nmicro seconds : %i\n\n",
// 		law.begin.tv_sec, law.begin.tv_usec);
// printf("seconds : %ld\nmicro seconds : %i\n\n",
// 		law.philos[0].last_meal.tv_sec, law.philos[0].last_meal.tv_usec);

void	print_timestamp(t_philosopher *philo, struct timeval starting_time,
							int position, enum e_state state)
{
	int	time_stamp;

	time_stamp = gettimestamp(starting_time);
	sem_wait(philo->law->printf_sem);
	if (state == 0)
		printf("%i\t%i died\n", time_stamp, position);
	if (state == 1)
		printf("%i\t%i is eating\n", time_stamp, position);
	if (state == 2)
		printf("%i\t%i is thinking\n", time_stamp, position);
	if (state == 3)
		printf("%i\t%i is sleeping\n", time_stamp, position);
	if (state == 4)
		printf("%i\t%i has taken a fork\n", time_stamp, position);
	sem_post(philo->law->printf_sem);
}

// int	check_death_row(t_philosopher *philo)
// {
// 	if (sem_open("/finish", 0) != SEM_FAILED)
// 		return (1);
// 	return (0);
// }

int	will_i_die(t_philosopher *philo, int time_survive)
{
	if ((double)gettimestamp(philo->last_meal) + (double)time_survive
		> (double)philo->law->time_die)
	{
		ft_usleep(philo->law->time_die - gettimestamp(philo->last_meal));
		if (sem_open("/finish", 0) != SEM_FAILED)
			return (1);
		philo->state = DEAD;
		print_timestamp(philo, philo->law->begin, philo->position, DEAD);
		sem_open("/finish", O_CREAT, 0644, 1);
		return (1);
	}
	return (0);
}
