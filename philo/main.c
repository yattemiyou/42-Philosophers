/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:36:08 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/10 15:13:27 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char const *argv[])
{
	t_sim	sim;
	t_philo	*philos;

	if (initialize(argc, argv, &sim, &philos) == FALSE)
		return (1);
	if (start(&sim, philos) == FALSE)
		return (finalize(&sim, philos), 1);
	if (wait(&sim, philos) == FALSE)
		return (finalize(&sim, philos), 1);
	return (finalize(&sim, philos), 0);
}
