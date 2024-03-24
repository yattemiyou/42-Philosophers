/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:46:55 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/24 15:04:07 by anonymous        ###   ########.fr       */
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

int	take_fork(t_philo *philo, int first, int second)
{
	if (pthread_mutex_lock(&(philo->sim->fork[first])) != 0)
		return (FALSE);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(&(philo->sim->fork[second])) != 0)
		return (FALSE);
	print_status(philo, "has taken a fork");
	return (TRUE);
}

int	put_fork(t_philo *philo, int first, int second)
{
	if (pthread_mutex_unlock(&(philo->sim->fork[second])) != 0)
		return (FALSE);
	if (pthread_mutex_unlock(&(philo->sim->fork[first])) != 0)
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
