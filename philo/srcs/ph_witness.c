/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_witness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:00:03 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/23 17:00:04 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static size_t	ft_witness_compare_time(t_ph *p)
{
	if (ft_get_time() - p->lst_eaten > p->m->arg->death_time)
	{
		pthread_mutex_lock(&p->mut->mu_witness_time_chk);
		p->die_chk = 1;
		p->m->die_monitor = 1;
		ft_philo_said(p->id, "died", p);
		pthread_mutex_unlock(&p->mut->mu_witness_time_chk);
		return (1);
	}
	return (0);
}

static size_t	ft_witness_chk(t_main *m)
{
	size_t	i;
	size_t	philo_eaten;

	pthread_mutex_lock(&m->mut->mu_die_chk);
	if (m->die_monitor)
		return (ft_if_die_unlock(&m->mut->mu_die_chk, 1));
	i = 0;
	philo_eaten = 0;
	while (i < (size_t) m->arg->n)
	{
		if (m->ph[i]->eaten >= (size_t) m->arg->eat_cnt && \
				m->arg->eat_cnt > 0)
			philo_eaten++;
		if (ft_witness_compare_time(m->ph[i]) == 1)
		{
			pthread_mutex_unlock(&m->mut->mu_die_chk);
			return (1);
		}
			
		i++;
	}
	pthread_mutex_unlock(&m->mut->mu_die_chk);
	return (philo_eaten);
}

void	*ft_witness(void *arg)
{
	t_main	*m;
	size_t	die;

	m = (t_main *)arg;
	die = 1;
	while (die)
	{
		if ((int)ft_witness_chk(m) == (int) m->arg->n)
		{
			m->die_monitor = 2;
			return (NULL);
		}
	}
	return (NULL);
}
