/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:07:18 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 05:33:42 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

enum e_state {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	GRAB
} ;

typedef struct s_philosopher
{
	int					position;
	enum e_state		state;
	int					meals_left;
	struct timeval		last_meal;
	struct s_law		*law;
}				t_philosopher;

typedef struct s_law
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals;
	struct timeval	begin;
	sem_t			*forks;
	sem_t			*printf_sem;
}				t_law;

// philo_factory

int		set_table(t_law *law);

// philo

int		routine(t_philosopher *philo);

// philo_states

int		philo_eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
int		philo_think(t_philosopher *philo, int milliseconds);

// philo_utils

int		gettimestamp(struct timeval starting_time);
void	print_timestamp(t_philosopher *philo, struct timeval starting_time, \
							int position, enum e_state state);
int		will_i_die(t_philosopher *philo, int var);

// utils

int		ft_atoi(const char *str, int *result);
void	ft_usleep(int microsecs);

#endif
