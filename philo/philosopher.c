/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:07:24 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/17 22:15:39 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_value(t_philo *philo, int *ptr, int *value)
{
	pthread_mutex_lock(&(philo->lock));
	*value = *ptr;
	pthread_mutex_unlock(&(philo->lock));
	return (TRUE);
}

int	set_value(t_philo *philo, int *ptr, int value)
{
	pthread_mutex_lock(&(philo->lock));
	*ptr = value;
	pthread_mutex_unlock(&(philo->lock));
	return (TRUE);
}

static int	do_something(t_philo *philo, char *something, int msec)
{
	int64_t	start_time;

	start_time = get_time();
	printf("%zd %d is %s\n", (int64_t)(start_time - philo->sim->start_time), philo->id, something);
	while (get_time() - start_time < msec)
	{
		if (usleep(100) == -1)
			return (printf("%s\n", MSG04), FALSE);
	}
	return (TRUE);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	int first;
	int second;

	if (philo->id % 2)
	{
		first = philo->id;
		second = (philo->id - 1 + philo->sim->number) % philo->sim->number;
	}
	else
	{
		first = (philo->id - 1 + philo->sim->number) % philo->sim->number;
		second = philo->id;
	}

	while (get_time() - philo->last_meal < philo->sim->die)
	{
		pthread_mutex_lock(&(philo->sim->fork[first]));
		printf("%zd %d has taken a fork\n", (int64_t)(get_time() - philo->sim->start_time), philo->id);

		pthread_mutex_lock(&(philo->sim->fork[second]));
		printf("%zd %d has taken a fork\n", (int64_t)(get_time() - philo->sim->start_time), philo->id);

		do_something(philo, "eating", philo->sim->eat);
		philo->last_meal = get_time();

		pthread_mutex_unlock(&(philo->sim->fork[first]));
		pthread_mutex_unlock(&(philo->sim->fork[second]));

		do_something(philo, "sleeping", philo->sim->sleep);

		printf("%zd %d is thinking\n", (int64_t)(get_time() - philo->sim->start_time), philo->id);
	}
	printf("%zd %d died\n", get_time() - philo->sim->start_time, philo->id);
	return (NULL);
}
