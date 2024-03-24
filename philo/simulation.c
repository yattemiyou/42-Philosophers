/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:15:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/24 14:11:50 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize(int argc, char const *argv[], t_sim *sim, t_philo **philos)
{
	if (argc != 5 && argc != 6)
		return (printf("%s\n", MSG01), FALSE);
	sim->number = atoi(argv[1]);
	sim->die = atoi(argv[2]);
	sim->eat = atoi(argv[3]);
	sim->sleep = atoi(argv[4]);
	if (argc == 6)
		sim->times = atoi(argv[5]);

	if (initialize_fork(sim) == FALSE)
		return (FALSE);

	*philos = malloc(sim->number * sizeof(t_philo));
	if (*philos == NULL)
		return (finalize(sim, *philos), printf("%s\n", MSG02), FALSE);
	return (TRUE);
}

void	finalize(t_sim *sim, t_philo *philos)
{
	finalize_fork(sim);
	free(philos);
}

int	start(t_sim *sim, t_philo *philos)
{
	int	i;

	sim->start_time = get_time();

	i = 0;
	while (i < sim->number)
	{
		philos[i].sim = sim;
		pthread_mutex_init(&(philos[i].lock), NULL);

		philos[i].id = i;
		philos[i].last_meal = sim->start_time;
		philos[i].died = FALSE;
		philos[i].termination = FALSE;

		void *arg = &(philos[i]);

		if (pthread_create(&(philos[i].tid), NULL, run, arg) != 0)
			return printf("%s\n", MSG03), FALSE;
		i++;
	}

	return (TRUE);
}

int	sim_wait(t_sim *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		if (pthread_join(philos[i].tid, NULL) != 0)
			return printf("%s\n", MSG05), FALSE;
		i++;
	}

	return (TRUE);
}

int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FALSE);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
