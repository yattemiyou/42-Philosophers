/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:07:24 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/10 15:53:44 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	do_something(t_philo *philo, char *something, int msec)
{
	int64_t	start_time;

	start_time = get_time() - philo->sim->start_time;
	printf("%zd %d is %s\n", start_time, philo->id, something);
	while (msec > 0)
	{
		if (usleep(100) == -1)
			return (printf("%s\n", MSG04), FALSE);
		msec -= (get_time() - start_time);
	}
	return (TRUE);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->lifetime > 0)
	{
		do_something(philo, "eating", philo->sim->eat);
		philo->last_meal = get_time();
		philo->lifetime = philo->sim->die;
		do_something(philo, "sleeping", philo->sim->sleep);
		philo->lifetime -= (get_time() - philo->last_meal);
	}
	return (NULL);
}
