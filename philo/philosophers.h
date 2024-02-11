/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:03:26 by anonymous         #+#    #+#             */
/*   Updated: 2024/02/11 15:23:07 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

# define MSG01 "起動引数が不正です。"
# define MSG02 "メモリの確保に失敗しました。"
# define MSG03 "スレッドの生成に失敗しました。"
# define MSG04 "スリーブに失敗しました。"
# define MSG05 "スレッドの終了待ちに失敗しました。"

typedef struct s_simulation		t_sim;
typedef struct s_philosopher	t_philo;
typedef struct s_mutex			t_mutex;

struct s_simulation
{
	int		number;
	int		die;
	int		eat;
	int		sleep;
	int		times;

	pthread_mutex_t	*fork;
	int64_t	start_time;
};

struct s_philosopher
{
	t_sim		*sim;

	pthread_t	tid;
	int			id;
	int64_t		last_meal;
};

// simulation.c
int		initialize(int argc, char const *argv[], t_sim *sim, t_philo **philos);
void	finalize(t_sim *sim, t_philo *philos);
int		start(t_sim *sim, t_philo *philos);
int		sim_wait(t_sim *sim, t_philo *philos);
int64_t	get_time(void);

// philosopher.c
void	*run(void *arg);

#endif
