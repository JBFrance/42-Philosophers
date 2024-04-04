/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:36:43 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/30 14:36:46 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	norm_helper(t_monitor *monitor, t_philo *philo, int *stop, int *lim)
{
	eating(philo);
	writing("is sleeping", philo);
	my_slp(monitor->time_to_sleep, monitor);
	writing("is thinking", philo);
	pthread_mutex_lock(&monitor->stop_mutex);
	*stop = monitor->stop_condition;
	pthread_mutex_unlock(&monitor->stop_mutex);
	pthread_mutex_lock(&monitor->eat_lim_mutex);
	*lim = monitor->eat_lim;
	pthread_mutex_unlock(&monitor->eat_lim_mutex);
}

static void	*routine(void *params)
{
	int			i;
	int			stop;
	int			lim;
	t_philo		*philo;
	t_monitor	*monitor;

	i = 0;
	philo = (t_philo *)params;
	monitor = philo->monitor;
	if (philo->index % 2 && monitor->count > 1)
		my_slp(monitor->time_to_eat / 50, monitor);
	pthread_mutex_lock(&monitor->stop_mutex);
	stop = monitor->stop_condition;
	pthread_mutex_unlock(&monitor->stop_mutex);
	pthread_mutex_lock(&monitor->eat_lim_mutex);
	lim = monitor->eat_lim;
	pthread_mutex_unlock(&monitor->eat_lim_mutex);
	while (!stop && !lim)
	{
		norm_helper(monitor, philo, &stop, &lim);
	}
	return (NULL);
}

static void	exit_threads(t_monitor *monitor)
{
	int	i;

	if (monitor->count == 1)
		pthread_detach(monitor->philos[0].track);
	else
	{
		i = -1;
		while (++i < monitor->count)
			pthread_join(monitor->philos[i].track, NULL);
	}
	i = -1;
	while (++i < monitor->count)
		pthread_mutex_destroy(&monitor->forks[i]);
	pthread_mutex_destroy(&monitor->meal);
	pthread_mutex_destroy(&monitor->to_write);
	pthread_mutex_destroy(&monitor->stop_mutex);
	pthread_mutex_destroy(&monitor->eat_lim_mutex);
	pthread_mutex_destroy(&monitor->e_lst_mutex);
	pthread_mutex_destroy(&monitor->c_max_mutex);
	pthread_mutex_destroy(&monitor->count_mutex);
	i = -1;
	while (++i < monitor->count)
		free(monitor->philos[i].index_str);
	free(monitor->philos);
	free(monitor->forks);
}

int	threads_init(t_monitor *monitor)
{
	int	i;

	i = -1;
	monitor->start_time = get_time();
	while (++i < monitor->count)
	{
		monitor->philos[i].last_ate = get_time();
		if (pthread_create(&monitor->philos[i].track, \
		NULL, routine, &(monitor->philos[i])))
			return (0);
	}
	is_dead(monitor, monitor->philos);
	pthread_mutex_unlock(&monitor->to_write);
	exit_threads(monitor);
	return (1);
}

void	my_slp(unsigned long duration, t_monitor *monitor)
{
	unsigned long	start;
	int				check;

	pthread_mutex_lock(&monitor->stop_mutex);
	check = monitor->stop_condition;
	pthread_mutex_unlock(&monitor->stop_mutex);
	start = get_time();
	while (!check)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(monitor->count * 2);
		pthread_mutex_lock(&monitor->stop_mutex);
		check = monitor->stop_condition;
		pthread_mutex_unlock(&monitor->stop_mutex);
	}
}
