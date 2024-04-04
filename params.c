/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:48:40 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/28 14:48:42 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	extra_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	parsing(t_monitor *monitor, int argc, char *argv[], int i)
{
	while (i < argc)
	{
		if (!(argv[i]))
			return (0);
		if (!extra_check(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	monitor->count = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		monitor->eat_count_max = ft_atoi(argv[5]);
	else
		monitor->eat_count_max = 0;
	if (monitor->count < 1 || monitor->time_to_die < 0 \
	|| monitor->time_to_eat < 0
		|| monitor->time_to_sleep < 0 || monitor->eat_count_max < 0)
		return (0);
	return (1);
}

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}
