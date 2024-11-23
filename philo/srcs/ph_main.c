/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:50:27 by jaehukim          #+#    #+#             */
/*   Updated: 2024/11/18 17:50:29 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char *av[])
{
	t_main	*main;

	ft_initalisation(ac, av, &main);
	ft_naissance_philo(main);
	ft_destroy_all(&main);
}
