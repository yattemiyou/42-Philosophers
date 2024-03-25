/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:07:24 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/25 09:16:03 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_terminated(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&(philo->lock));
	ret = philo->terminated;
	pthread_mutex_unlock(&(philo->lock));
	return (ret);
}

void	terminate(t_philo *philo)
{
	pthread_mutex_lock(&(philo->lock));
	philo->terminated = TRUE;
	pthread_mutex_unlock(&(philo->lock));
}

static int	do_something(t_philo *philo, int msec)
{
	int64_t	now;
	int64_t	start_time;

	now = get_time();
	start_time = now;
	while (now - start_time < msec)
	{
		if (is_terminated(philo))
			return (FALSE);
		if (now - philo->last_meal >= philo->sim->die)
			return (print_status(philo, "died"), FALSE);
		if (usleep(100) == -1)
			return (printf("%s\n", MSG04), FALSE);
		now = get_time();
	}
	return (TRUE);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		take_fork(philo);
		print_status(philo, "is eating");
		if (do_something(philo, philo->sim->eat) == FALSE)
		{
			put_fork(philo);
			break ;
		}
		philo->last_meal = get_time();
		put_fork(philo);
		if (philo->sim->times > 0 && ++philo->meals >= philo->sim->times)
			break ;
		print_status(philo, "is sleeping");
		if (do_something(philo, philo->sim->sleep) == FALSE)
			break ;
		print_status(philo, "is thinking");
	}
	terminate(philo);
	return (NULL);
}
