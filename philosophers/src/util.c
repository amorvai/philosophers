/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:22:22 by amorvai           #+#    #+#             */
/*   Updated: 2022/12/28 15:08:40 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

void	get_sign(const char *str, int *sign, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str, int *result)
{
	long	n;
	int		i;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	if (!str || str[i] == '\0')
		return (2);
	get_sign(str, &sign, &i);
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		if (sign == 1 && n > 2147483647)
			return (1);
		else if (sign == -1 && n > 2147483648)
			return (1);
		i++;
	}
	if (str[i] != '\0')
		return (1);
	*result = (int)(n * sign);
	return (0);
}

void	ft_usleep(int millisecs)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	if (millisecs > 5)
		usleep((millisecs - 5) * 1000);
	while (gettimestamp(begin) < millisecs)
		;
}

void	free_setup(t_law *law, int i, int y)
{
	int	j;

	j = 0;
	pthread_mutex_destroy(&law->printf_mutex);
	while (j < i)
	{
		pthread_mutex_destroy(&law->forks[j].mutex);
		pthread_mutex_destroy(&law->philos[j].meals_mutex);
		pthread_mutex_destroy(&law->philos[j].termination_mutex);
		j++;
	}
	if (y >= 1)
		pthread_mutex_destroy(&law->forks[j].mutex);
	if (y == 2)
		pthread_mutex_destroy(&law->philos[j].meals_mutex);
	free(law->philos);
	free(law->forks);
}
