/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:03:26 by anonymous         #+#    #+#             */
/*   Updated: 2024/03/26 19:50:46 by anonymous        ###   ########.fr       */
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

struct s_simulation
{
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				times;
	pthread_mutex_t	*fork;
	int64_t			start_time;
	pthread_mutex_t	start_line;
};

struct s_philosopher
{
	t_sim			*sim;

	pthread_t		tid;
	pthread_mutex_t	lock;

	int				id;
	int				first;
	int				second;
	int64_t			last_meal;
	int				meals;
	int				terminated;
	int				is_full;
};

// fork.c
int		initialize_fork(t_sim *sim);
void	get_available_fork(t_philo *philo);
int		take_fork(t_philo *philo);
int		put_fork(t_philo *philo);
void	finalize_fork(t_sim *sim);

// simulation.c
int		initialize(int argc, char const *argv[], t_sim *sim, t_philo **philos);
void	finalize(t_sim *sim, t_philo *philos);
int		start(t_sim *sim, t_philo *philos);

// philosopher.c
void	*run(void *arg);
int		do_something(t_philo *philo, int msec);
int		is_terminated(t_philo *philo);
void	terminate(t_philo *philo);

// util.c
int		ft_atoi(const char *nptr);
int64_t	get_time(void);
void	print_status(t_philo *philo, char *status, int died);

#endif
