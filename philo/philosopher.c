/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:07:24 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/05 21:57:14 by anonymous        ###   ########.fr       */
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

static void	print_status(t_philo *philo, char *status)
{
	u_int32_t dt = get_time() - philo->sim->start_time;

	printf("%u %d %s\n", dt, philo->id + 1, status);
}

static int	do_something(int msec)
{
	int64_t	start_time;

	start_time = get_time();
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
		print_status(philo, "has taken a fork");

		pthread_mutex_lock(&(philo->sim->fork[second]));
		print_status(philo, "has taken a fork");

		print_status(philo, "is eating");
		do_something(philo->sim->eat);
		philo->last_meal = get_time();

		pthread_mutex_unlock(&(philo->sim->fork[first]));
		pthread_mutex_unlock(&(philo->sim->fork[second]));

		print_status(philo, "is sleeping");
		do_something(philo->sim->sleep);

		print_status(philo, "is thinking");
	}
	print_status(philo, "died");
	return (NULL);
}
