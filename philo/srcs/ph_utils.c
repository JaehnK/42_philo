/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:55:46 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/18 17:55:48 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *msg)
{
	int	err;

	err = errno;
	if (err)
		perror(msg);
	else
		printf("Philo : %s\n", msg);
	exit(errno);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + \
			(long long)time.tv_usec / 1000);
}

int	ft_usleep(long long time)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_usleep2(long long time, t_ph *p)
{
	long long	start;
	int			flag;

	flag = 0;
	start = ft_get_time();
	while ((ft_get_time() - start) < time && !flag)
	{
		flag = ft_die_check(p);
		usleep(time / 10);
	}
	return (0);
}

void	ft_philo_said(size_t idx, char *msg, t_ph *p)
{
	long long		ts;
	size_t			i;

	i = pthread_mutex_lock(&p->mut->mu_said);
	if (i)
		printf("%zu Mutex Lock Error(said)\n", i);
	ts = ft_get_time() - p->start;
	printf("%lld %zu %s\n", ts, idx, msg);
	pthread_mutex_unlock(&p->mut->mu_said);
	return ;
}
