/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:36:24 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/19 08:36:26 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_if_die_unlock(pthread_mutex_t *mtx, int flag)
{
	pthread_mutex_unlock(mtx);
	return (flag);
}

size_t	ft_die_check(t_ph *p)
{
	size_t	flag;

	pthread_mutex_lock(&p->mut->mu_die_chk);
	flag = 0;
	if (p->die_chk == 1)
		return (ft_if_die_unlock(&p->mut->mu_die_chk, 1));
	if (ft_get_time() - p->lst_eaten > p->m->arg->death_time)
		p->die_chk = 1;
	if (p->m->arg->eat_cnt > 0 && \
			p->m->arg->eat_cnt < (ssize_t) p->eaten)
		p->die_chk = 1;
	if (p->m->die_monitor)
		return (ft_if_die_unlock(&p->mut->mu_die_chk, 1));
	flag = p->die_chk;
	if (flag)
	{
		p->m->die_monitor = 1;
		ft_philo_said(p->id, "died", p);
	}	
	pthread_mutex_unlock(&p->mut->mu_die_chk);
	return (flag);
}

static int	ft_sleep(t_ph *p)
{
	if (ft_die_check(p))
		return (1);
	ft_philo_said(p->id, "is sleeping", p);
	ft_usleep2(p->m->arg->sleep_time, p);
	if (ft_die_check(p))
		return (1);
	return (0);
}

void	*ft_routine(void *p)
{
	t_ph	*ph;

	ph = (t_ph *) p;
	ft_philo_said(ph->id, "is thinking", ph);
	if (ph->m->arg->n == 1)
	{
		ft_usleep(ph->m->arg->death_time);
		ft_philo_said(ph->id, "died", p);
		return (NULL);
	}
	if (ph->id % 2 == 1)
		ft_usleep(100);
	while (1)
	{
		if (ft_eat(ph) == 1)
			break ;
		if (ft_sleep(ph) == 1)
			break ;
		if (ft_die_check(ph) == 1)
			break ;
		ft_philo_said(ph->id, "is thinking", ph);
	}
	return (NULL);
}
