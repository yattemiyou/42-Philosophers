/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:47 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/25 21:52:58 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status, int died)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	static int				flag = FALSE;
	u_int32_t				delta_t;

	pthread_mutex_lock(&lock);
	delta_t = get_time() - philo->sim->start_time;
	if (!flag)
		printf("%u %d %s\n", delta_t, philo->id + 1, status);
	if (died)
		flag = TRUE;
	pthread_mutex_unlock(&lock);
}
