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
		printf("Check time with witness\n");
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

	pthread_mutex_lock(&m->mut->mu_witness);
	if (m->die_monitor)
		return (ft_if_die_unlock(&m->mut->mu_witness, 1));
	i = 0;
	philo_eaten = 0;
	while (i < (size_t) m->arg->n)
	{
		if (m->ph[i]->eaten >= (size_t) m->arg->eat_cnt && \
				m->arg->eat_cnt > 0)
			philo_eaten++;
		if (ft_witness_compare_time(m->ph[i]) == 1)
			return (1);
		i++;
	}
	pthread_mutex_unlock(&m->mut->mu_witness);
	return (philo_eaten == (size_t)m->arg->n);
}

void	*ft_witness(void *arg)
{
	t_main	*m;
	size_t	die;

	m = (t_main *)arg;
	die = 1;
	while (die)
	{
		if (ft_witness_chk(m) == 1)
			die = 0;
	}
	return (NULL);
}
