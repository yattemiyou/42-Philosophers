/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:15:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/25 09:13:05 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize(int argc, char const *argv[], t_sim *sim, t_philo **philos)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("%s\n", MSG01), FALSE);
	sim->number = atoi(argv[1]);
	sim->die = atoi(argv[2]);
	sim->eat = atoi(argv[3]);
	sim->sleep = atoi(argv[4]);
	sim->times = -1;
	if (argc == 6)
		sim->times = atoi(argv[5]);
	if (initialize_fork(sim) == FALSE)
		return (FALSE);
	*philos = malloc(sim->number * sizeof(t_philo));
	if (*philos == NULL)
		return (finalize(sim, *philos), printf("%s\n", MSG02), FALSE);
	i = 0;
	while (i < sim->number)
	{
		(*philos)[i].sim = sim;
		pthread_mutex_init(&((*philos)[i].lock), NULL);
		(*philos)[i].id = i;
		get_available_fork(&((*philos)[i]));
		(*philos)[i++].terminated = FALSE;
	}
	return (TRUE);
}

void	finalize(t_sim *sim, t_philo *philos)
{
	int	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < sim->number)
		{
			terminate(&philos[i]);
			if (pthread_join(philos[i].tid, NULL) != 0)
				printf("%s\n", MSG05);
			pthread_mutex_destroy(&(philos[i].lock));
			i++;
		}
		free(philos);
	}
	finalize_fork(sim);
}

int	start(t_sim *sim, t_philo *philos)
{
	t_philo	*philo;
	int		i;

	sim->start_time = get_time();
	i = 0;
	while (i < sim->number)
	{
		philo = &(philos[i]);
		philo->last_meal = sim->start_time;
		philo->meals = 0;
		if (pthread_create(&(philo->tid), NULL, run, philo) != 0)
			return (printf("%s\n", MSG03), FALSE);
		i++;
	}
	return (TRUE);
}
