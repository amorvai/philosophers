/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:07:18 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 00:16:58 by amorvai          ###   ########.fr       */
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
	// int				position;
	// int				locked;
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
	int					die_now_bitch;
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
}				t_law;




int		get_law(int argc, char **argv, t_law *law);
int		setup_philos(t_law *law);
int		setoff_philos(t_law *law);

void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str, int *result);
void	ft_usleep(int microsecs);

void	*routine(void *random_philo);
void	*boss(void *law2);
int		gettimestamp(struct timeval starting_time);
void	print_timestamp(struct timeval starting_time, int position, enum state state);

void	eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
int		think(t_philosopher *philo, int	milliseconds);
int		will_i_die(t_philosopher *philo, int var);


// int		gettimestamp_mod(struct timeval starting_time, struct timeval current_time);

#endif
