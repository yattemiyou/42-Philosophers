/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:15:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/10 12:34:34 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize(int argc, char const *argv[], t_simulation *sim)
{
	if (argc != 3)
		return (printf("%s\n", MSG01), FALSE);
	sim->number = atoi(argv[1]);
	sim->die = atoi(argv[2]);
	return (TRUE);
}

int64_t	get_simulation_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FALSE);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
