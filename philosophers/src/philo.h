/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:07:18 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/26 22:52:17 by amorvai          ###   ########.fr       */
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

enum state {
	DEAD, EAT, THINK, SLEEP, GRAB
} ;

typedef struct s_fork
{
	int				position;
	int				locked;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_philosopher
{
	int					position;
	enum state			state;
	pthread_t			thread;
	t_fork				*r_fork;
	t_fork				*l_fork;
	int					meals_left;
	struct timeval		last_meal;
	const struct s_law	*law;
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
}				t_law;


void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str, int *result);

int		get_law(int argc, char **argv, t_law *law);
int		init_philos(t_law *law);
int		gettimestamp(struct timeval	starting_time);
void	print_timestamp(struct timeval starting_time, int position, enum state state);
int		gettimestamp_mod(struct timeval starting_time, struct timeval current_time);
void	ft_usleep(int microsecs);
void	*routine(void *random_philo);

#endif