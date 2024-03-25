/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:36:08 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/25 23:12:49 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	watch(t_sim *sim, t_philo *philos)
{
	int	is_full;
	int	i;

	while (TRUE)
	{
		is_full = TRUE;
		i = 0;
		while (i < sim->number)
		{
			if (is_terminated(&philos[i++]))
			{
				if (sim->times < 0)
					return (TRUE);
				continue ;
			}
			is_full = FALSE;
		}
		if (is_full)
			return (TRUE);
		if (usleep(100) == -1)
			return (printf("%s\n", MSG04), FALSE);
	}
}

int	main(int argc, char const *argv[])
{
	t_sim	sim;
	t_philo	*philos;

	if (initialize(argc, argv, &sim, &philos) == FALSE)
		return (1);
	if (start(&sim, philos) == FALSE)
		return (finalize(&sim, philos), 1);
	if (watch(&sim, philos) == FALSE)
		return (finalize(&sim, philos), 1);
	return (finalize(&sim, philos), 0);
}
