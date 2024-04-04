/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:36:31 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/30 14:36:36 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	writing(char *msg, t_philo *philo)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->monitor->start_time);
	pthread_mutex_lock(&philo->monitor->to_write);
	pthread_mutex_lock(&philo->monitor->stop_mutex);
	pthread_mutex_lock(&philo->monitor->eat_lim_mutex);
	if (!philo->monitor->stop_condition && !philo->monitor->eat_lim)
		printf("%s %s %s\n", timestamp, philo->index_str, msg);
	pthread_mutex_unlock(&philo->monitor->stop_mutex);
	pthread_mutex_unlock(&philo->monitor->eat_lim_mutex);
	pthread_mutex_unlock(&philo->monitor->to_write);
	free(timestamp);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->forks[philo->r_fork]);
	writing("has taken a fork", philo);
	pthread_mutex_lock(&philo->monitor->forks[philo->l_fork]);
	writing("has taken a fork", philo);
	pthread_mutex_lock(&philo->monitor->meal);
	writing("is eating", philo);
	pthread_mutex_lock(&philo->la_ate_mutex);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->la_ate_mutex);
	pthread_mutex_unlock(&philo->monitor->meal);
	my_slp(philo->monitor->time_to_eat, philo->monitor);
	philo->eaten++;
	pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork]);
}

static void	d_help2(t_monitor *monitor, t_philo *philo, int i)
{
	t_helper	help;

	pthread_mutex_unlock(&monitor->stop_mutex);
	i = 0;
	pthread_mutex_lock(&monitor->c_max_mutex);
	help.max_help = monitor->eat_count_max;
	pthread_mutex_unlock(&monitor->c_max_mutex);
	pthread_mutex_lock(&monitor->count_mutex);
	help.count_help = monitor->count;
	pthread_mutex_unlock(&monitor->count_mutex);
	while (help.max_help && i < help.count_help \
	&& philo[i].eaten >= help.max_help)
		i++;
	pthread_mutex_lock(&monitor->eat_lim_mutex);
	pthread_mutex_lock(&monitor->count_mutex);
	monitor->eat_lim = (i == monitor->count);
	pthread_mutex_unlock(&monitor->count_mutex);
	pthread_mutex_unlock(&monitor->eat_lim_mutex);
}

static void	d_help(t_monitor *monitor, t_philo *philo, int stop, int i)
{
	pthread_mutex_lock(&monitor->meal);
	pthread_mutex_lock(&philo[i].la_ate_mutex);
	if ((int)(get_time() - philo[i].last_ate) >= monitor->time_to_die)
	{
		pthread_mutex_unlock(&monitor->meal);
		pthread_mutex_unlock(&philo[i].la_ate_mutex);
		writing("died", &philo[i]);
		pthread_mutex_lock(&monitor->stop_mutex);
		monitor->stop_condition = 1;
		stop = monitor->stop_condition;
		pthread_mutex_unlock(&monitor->stop_mutex);
	}
	pthread_mutex_unlock(&philo[i].la_ate_mutex);
	pthread_mutex_unlock(&monitor->meal);
}

void	is_dead(t_monitor *monitor, t_philo *philo)
{
	int			i;
	int			stop;

	pthread_mutex_lock(&monitor->eat_lim_mutex);
	while (!monitor->eat_lim)
	{
		pthread_mutex_unlock(&monitor->eat_lim_mutex);
		i = -1;
		pthread_mutex_lock(&monitor->stop_mutex);
		stop = monitor->stop_condition;
		pthread_mutex_unlock(&monitor->stop_mutex);
		while (++i < monitor->count && !stop)
			d_help(monitor, philo, stop, i);
		pthread_mutex_lock(&monitor->stop_mutex);
		if (monitor->stop_condition)
		{
			pthread_mutex_unlock(&monitor->stop_mutex);
			break ;
		}
		d_help2(monitor, philo, i);
	}
	pthread_mutex_unlock(&monitor->eat_lim_mutex);
}
