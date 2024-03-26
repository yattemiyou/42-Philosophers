/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:15:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/26 20:27:28 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_param(int argc, char const *argv[], t_sim *sim)
{
	if (argc != 5 && argc != 6)
		return (FALSE);
	sim->number = ft_atoi(argv[1]);
	if (sim->number < 0)
		return (FALSE);
	sim->die = ft_atoi(argv[2]);
	if (sim->die < 0)
		return (FALSE);
	sim->eat = ft_atoi(argv[3]);
	if (sim->eat < 0)
		return (FALSE);
	sim->sleep = ft_atoi(argv[4]);
	if (sim->sleep < 0)
		return (FALSE);
	sim->times = -1;
	if (argc == 6)
	{
		sim->times = ft_atoi(argv[5]);
		if (sim->times < 0)
			return (FALSE);
		if (sim->times == 0)
			sim->number = 0;
	}
	sim->interruption = FALSE;
	return (TRUE);
}

int	initialize(int argc, char const *argv[], t_sim *sim, t_philo **philos)
{
	int	i;

	if (get_param(argc, argv, sim) == FALSE)
		return (printf("%s\n", MSG01), FALSE);
	if (initialize_fork(sim) == FALSE)
		return (FALSE);
	pthread_mutex_init(&sim->start_line, NULL);
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
		(*philos)[i].terminated = FALSE;
		(*philos)[i++].is_full = FALSE;
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
	pthread_mutex_destroy(&sim->start_line);
}

int	start(t_sim *sim, t_philo *philos)
{
	t_philo	*philo;
	int		i;

	pthread_mutex_lock(&sim->start_line);
	sim->start_time = get_time();
	i = 0;
	while (i < sim->number)
	{
		philo = &(philos[i]);
		philo->last_meal = sim->start_time;
		philo->meals = 0;
		if (pthread_create(&(philo->tid), NULL, run, philo) != 0)
		{
			printf("%s\n", MSG03);
			sim->interruption = TRUE;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&sim->start_line);
	return (!sim->interruption);
}
