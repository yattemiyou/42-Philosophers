/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:46:55 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/26 15:43:43 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_fork(t_sim *sim)
{
	int	i;

	sim->fork = malloc(sim->number * sizeof(pthread_mutex_t));
	if (sim->fork == NULL)
		return (printf("%s\n", MSG02), FALSE);
	i = 0;
	while (i < sim->number)
		pthread_mutex_init(&(sim->fork[i++]), NULL);
	return (TRUE);
}

void	get_available_fork(t_philo *philo)
{
	if (philo->id % 2 || philo->id == philo->sim->number - 1)
	{
		philo->first = philo->id;
		philo->second = (philo->id + 1) % philo->sim->number;
	}
	else
	{
		philo->first = (philo->id + 1) % philo->sim->number;
		philo->second = philo->id;
	}
}

int	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->sim->fork[philo->first])) != 0)
		return (FALSE);
	print_status(philo, "has taken a fork", FALSE);
	if (&(philo->sim->fork[philo->first]) == &(philo->sim->fork[philo->second]))
	{
		do_something(philo, 0x7fffffff);
		return (FALSE);
	}
	if (pthread_mutex_lock(&(philo->sim->fork[philo->second])) != 0)
		return (FALSE);
	print_status(philo, "has taken a fork", FALSE);
	return (TRUE);
}

int	put_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->sim->fork[philo->second])) != 0)
		return (FALSE);
	if (pthread_mutex_unlock(&(philo->sim->fork[philo->first])) != 0)
		return (FALSE);
	return (TRUE);
}

void	finalize_fork(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
		pthread_mutex_destroy(&(sim->fork[i++]));
	free(sim->fork);
}
