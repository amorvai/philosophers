/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:07:18 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/31 01:23:38 by amorvai          ###   ########.fr       */
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

enum e_state {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	GRAB
} ;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_philosopher
{
	int					position;
	enum e_state		state;
	pthread_t			thread;
	t_fork				*r_fork;
	t_fork				*l_fork;
	int					meals_left;
	pthread_mutex_t		meals_mutex;
	struct timeval		last_meal;
	struct s_law		*law;
	int					die_now;
	pthread_mutex_t		termination_mutex;
}				t_philosopher;

typedef struct s_law
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals;
	struct timeval	begin;
	t_fork			*forks;
	t_philosopher	*philos;
	pthread_mutex_t	printf_mutex;
}				t_law;

// set_up

int		set_table(t_law *law);

int		set_up_philos(t_law *law);
void	set_last_meal_time(t_law *law);
int		set_off_philos(t_law *law);
void	free_setup(t_law *law, int i, int y);

// philo / philos_boss

void	*boss(void *law2);
void	*routine(void *random_philo);
void	lonely_philo(t_law *law);

// philo_states

int		philo_eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
int		philo_think(t_philosopher *philo, int milliseconds);

// utils_philo

int		gettimestamp(struct timeval starting_time);
void	print_timestamp(t_philosopher *philo, struct timeval starting_time, \
							int position, enum e_state state);
int		check_death_row(t_philosopher *philo);
int		will_i_die(t_philosopher *philo, int var);

// utils

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str, int *result);
void	ft_usleep(int microsecs);

#endif
