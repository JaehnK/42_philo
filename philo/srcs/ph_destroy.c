/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:26:02 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/19 10:26:03 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	destroy_fork(t_main **m)
{
	ssize_t	i;

	i = 0;
	while (i < (*m)->arg->n)
	{
		pthread_mutex_destroy(&(*m)->forks[i]);
		i++;
	}
	free((*m)->forks);
}

static void	destroy_philos(t_main **m)
{
	ssize_t	i;

	i = 0;
	while (i < (*m)->arg->n)
	{
		pthread_join(*(*m)->ph[i]->th, NULL);
		free((*m)->ph[i]->th);
		(*m)->ph[i]->mut = NULL;
		(*m)->ph[i]->forks = NULL;
		free((*m)->ph[i]);
		i++;
	}
}

static void	destroy_mutex(t_main **m)
{
	pthread_mutex_destroy(&(*m)->mut->mu_said);
	pthread_mutex_destroy(&(*m)->mut->mu_sleep);
	pthread_mutex_destroy(&(*m)->mut->mu_die_chk);
	free((*m)->mut);
}

void	ft_destroy_all(t_main **m)
{
	destroy_philos(m);
	destroy_fork(m);
	destroy_mutex(m);
	free((*m)->arg);
	free((*m)->ph);
	free((*m));
}
