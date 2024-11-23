/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:27 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/18 18:02:28 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static ssize_t	ft_atoi(char *str)
{
	int			idx;
	long long	ret;
	long long	base;

	idx = ft_strlen(str) - 1;
	ret = 0;
	base = 1;
	while (idx >= 0)
	{
		if (str[idx] < '0' || str[idx] > '9')
			ft_error("Invalid Arguments");
		ret += (str[idx] - '0') * base;
		base *= 10;
		idx--;
		if (ret > INT_MAX || base == 100000000000)
			ft_error("exceed INT_MAX");
	}
	return ((ssize_t) ret);
}

static void	ft_parse_arguments(int ac, char **av, t_main **m)
{
	if (ac < 5 || ac > 6)
		ft_error("Check The Argument Count");
	(*m)->arg->n = ft_atoi(av[1]);
	(*m)->arg->death_time = ft_atoi(av[2]);
	(*m)->arg->eat_time = ft_atoi(av[3]);
	(*m)->arg->sleep_time = ft_atoi(av[4]);
	if (ac == 5)
		(*m)->arg->eat_cnt = -1;
	else
		(*m)->arg->eat_cnt = ft_atoi(av[5]);
}

static void	ft_create_fork(t_main *m)
{
	int	i;

	i = 0;
	m->forks = malloc(sizeof(pthread_mutex_t) * (int) m->arg->n);
	if (!m->forks)
		ft_error("Allocation Error");
	while (i < m->arg->n)
	{
		if (pthread_mutex_init(&m->forks[i], 0) != 0)
			ft_error("Mutex Init Error");
		i++;
	}		
}

void	ft_initalisation(int ac, char **av, t_main **m)
{
	*m = (t_main *) malloc(sizeof(t_main) * 1);
	if (!*m)
		ft_error("Allocation Error");
	(*m)->arg = (t_arg *) malloc(sizeof(t_arg) * 1);
	if (!(*m)->arg)
		ft_error("Allocation Error");
	ft_parse_arguments(ac, av, m);
	(*m)->die_monitor = 0;
	ft_create_fork(*m);
}
