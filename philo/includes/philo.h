/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:51:15 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/18 17:51:18 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg
{
	ssize_t			n;
	ssize_t			death_time;
	ssize_t			eat_time;
	ssize_t			eat_cnt;
	ssize_t			sleep_time;
}	t_arg;

typedef struct s_mut
{
	pthread_mutex_t	mu_said;
	pthread_mutex_t	mu_sleep;
	pthread_mutex_t	mu_die_chk;
}	t_mut;

typedef struct s_ph
{
	size_t			id;
	pthread_t		*th;
	long long		start;
	long long		lst_eaten;
	size_t			eaten;
	size_t			l;
	size_t			r;
	size_t			die_chk;
	struct s_mut	*mut;
	struct s_main	*m;
	pthread_mutex_t	mu_meal;
	pthread_mutex_t	*forks;
}	t_ph;

typedef struct s_main
{
	t_arg			*arg;
	t_ph			**ph;
	t_mut			*mut;
	pthread_mutex_t	*forks;
	size_t			die_monitor;
}	t_main;

void		ft_error(char *msg);
long long	ft_get_time(void);
int			ft_usleep(long long time);
int			ft_usleep2(long long time, t_ph *p);
void		ft_philo_said(size_t idx, char *msg, t_ph *p);
void		ft_initalisation(int ac, char **av, t_main **m);
size_t		ft_die_check(t_ph *p);
void		ft_naissance_philo(t_main *m);
size_t		ft_if_die_unlock(pthread_mutex_t *mtx, int flag);
void		*ft_routine(void *ph);
int			ft_take_fork(t_ph *p);
int			ft_drop_fork(t_ph *p);
int			ft_eat(t_ph *p);
void		ft_destroy_all(t_main **m);
#endif