/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:11:37 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/20 17:11:38 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	get_fork_ord(t_ph *p, int *first, int *second)
{
	if (p->id == 0 && p->eaten == 0)
	{
		*first = p->r;
		*second = p->l;
	}
	else
	{
		*first = p->l;
		*second = p->r;
	}
}

int	ft_take_fork(t_ph *p)
{
	int	first;
	int	second;

	get_fork_ord(p, &first, &second);
	if (ft_die_check(p) == 1)
		return (1);
	pthread_mutex_lock(&p->m->forks[first]);
	if (ft_die_check(p) == 1)
	{
		pthread_mutex_unlock(&p->m->forks[first]);
		return (1);
	}
	else
		ft_philo_said(p->id, "has taken a fork", p);
	pthread_mutex_lock(&p->m->forks[second]);
	if (ft_die_check(p) == 1)
	{
		ft_drop_fork(p);
		return (1);
	}
	else
		ft_philo_said(p->id, "has taken a fork", p);
	return (0);
}

int	ft_drop_fork(t_ph *p)
{
	if (pthread_mutex_unlock(&p->m->forks[p->r]))
		printf("Mutex Unlock Error(right: %ld) %p \n", p->r, &p->m->forks[p->r]);
	if (pthread_mutex_unlock(&p->m->forks[p->l]))
		printf("Mutex Unlock Error(left: %ld) %p \n", p->l, &p->m->forks[p->l]);
	return (0);
}

int	ft_eat(t_ph *p)
{
	if (ft_die_check(p) == 1)
		return (1);
	if (ft_take_fork(p) == 1)
		return (1);
	if (ft_die_check(p) == 1)
	{
		ft_drop_fork(p);
		return (1);
	}
	p->eaten++;
	ft_philo_said(p->id, "is eating", p);
	p->lst_eaten = ft_get_time();
	ft_usleep2(p->m->arg->eat_time, p);
	if (ft_die_check(p))
	{
		ft_drop_fork(p);
		return (1);
	}
	ft_drop_fork(p);
	if (ft_die_check(p))
		return (1);
	return (0);
}
