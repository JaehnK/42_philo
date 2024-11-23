/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_naissance_ph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:21 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/18 19:43:22 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_create_mutex(pthread_mutex_t *m)
{
	if (pthread_mutex_init(m, NULL))
		ft_error("Mutex Init Error");
}

static t_mut	*ft_alloc_mutex(void)
{
	t_mut	*mut;

	mut = (t_mut *) malloc(sizeof(t_mut));
	if (!mut)
		ft_error("Allocation Error");
	memset(mut, 0, sizeof(t_mut));
	ft_create_mutex(&mut->mu_said);
	ft_create_mutex(&mut->mu_die_chk);
	ft_create_mutex(&mut->mu_sleep);
	return (mut);
}

static void	get_fork_num(t_ph *ph, size_t total)
{	
	if (ph->id == 0)
	{
		ph->l = total - 1;
		ph->r = ph->id;
	}
	else
	{
		ph->l = ph->id - 1;
		ph->r = ph->id;
	}
}

static void	ft_alloc_philo(size_t i, t_ph **ph, t_main *m)
{
	(*ph) = (t_ph *)malloc(sizeof(t_ph));
	if (!(*ph))
		ft_error("Philosopher Allocation Error");
	(*ph)->id = i;
	(*ph)->eaten = 0;
	(*ph)->die_chk = 0;
	(*ph)->lst_eaten = ft_get_time();
	(*ph)->start = ft_get_time();
	get_fork_num((*ph), m->arg->n);
	(*ph)->m = m;
	(*ph)->mut = m->mut;
	(*ph)->forks = m->forks;
	(*ph)->th = (pthread_t *) malloc(sizeof(pthread_t));
	ft_create_mutex(&(*ph)->mu_meal);
	if (!(*ph)->th)
		ft_error("Alloction Error");
}

void	ft_naissance_philo(t_main *m)
{
	size_t	i;

	i = 0;
	m->mut = ft_alloc_mutex();
	m->ph = (t_ph **) malloc(sizeof(t_ph *) * m->arg->n);
	while (i < (size_t) m->arg->n)
	{
		ft_alloc_philo(i, &m->ph[i], m);
		i++;
	}
	i = 0;
	while (i < (size_t) m->arg->n)
	{
		pthread_create(m->ph[i]->th, NULL, ft_routine, m->ph[i]);
		i++;
	}
}
