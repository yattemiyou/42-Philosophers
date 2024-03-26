/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:36:08 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/26 14:35:01 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	watch(t_sim *sim, t_philo *philos)
{
	int	is_all_full;
	int	i;

	while (TRUE)
	{
		is_all_full = TRUE;
		i = 0;
		while (i < sim->number)
		{
			if (is_terminated(&philos[i]))
			{
				if (philos[i].is_full == FALSE)
					return (TRUE);
				is_all_full &= TRUE;
			}
			else
				is_all_full &= FALSE;
			i++;
		}
		if (is_all_full)
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
