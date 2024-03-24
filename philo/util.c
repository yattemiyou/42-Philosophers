/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/24 15:02:40 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *status)
{
	u_int32_t	delta_t;

	delta_t = get_time() - philo->sim->start_time;
	printf("%u %d %s\n", delta_t, philo->id + 1, status);
}
