/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:11:46 by jfrances          #+#    #+#             */
/*   Updated: 2023/08/04 08:11:51 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	initialize_mutex(t_monitor*monitor)
{
	int	i;

	i = 0;
	while (i < monitor->count)
	{
		if (pthread_mutex_init(&(monitor->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&monitor->meal, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->to_write, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->stop_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->eat_lim_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->e_lst_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->c_max_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&monitor->count_mutex, NULL))
		return (1);
	return (0);
}

static int	initialize_philos(t_monitor*monitor)
{
	int	i;

	i = 0;
	while (i < monitor->count)
	{
		monitor->philos[i].eaten = 0;
		monitor->philos[i].index = i + 1;
		monitor->philos[i].index_str = ft_itoa(i + 1);
		if (!monitor->philos[i].index_str)
			break ;
		monitor->philos[i].r_fork = i;
		monitor->philos[i].l_fork = (i + 1) % monitor->count;
		monitor->philos[i].monitor = monitor;
		i++;
	}
	if (i != monitor->count)
	{
		while (i >= 0)
		{
			free(monitor->philos[i].index_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	initialize(t_monitor *monitor)
{
	monitor->philos = malloc(sizeof(t_philo) * monitor->count);
	if (!monitor->philos)
		return (0);
	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->count);
	if (!monitor->forks)
	{
		free(monitor->philos);
		return (0);
	}
	if (initialize_mutex(monitor))
	{
		free(monitor->philos);
		free(monitor->forks);
		return (0);
	}
	if (initialize_philos(monitor))
	{
		free(monitor->philos);
		free(monitor->forks);
		return (0);
	}
	return (1);
}
