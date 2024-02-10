/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:03:26 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/10 12:35:27 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define MSG01 "起動引数が不正です。"

typedef struct s_simulation	t_simulation;
typedef struct s_mutex		t_mutex;

struct s_simulation
{
	int		number;
	int		die;
	int		eat;
	int		sleep;
	int		times;

	int64_t	start_time;
};

struct s_mutex
{
	pthread_mutex_t	*fork;
};

// simulation.c
int		initialize(int argc, char const *argv[], t_simulation *sim);
int64_t	get_simulation_time(void);

#endif
