/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:35:45 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/28 14:35:46 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int argc, char *argv[])
{
	t_monitor	monitor;

	monitor.eat_lim = 0;
	monitor.stop_condition = 0;
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Number of Arguments\n"));
	if (!parsing(&monitor, argc, argv, 1))
		return (ft_error("ERROR: Invalid Input\n"));
	if (!initialize(&monitor))
		return (ft_error("Error: Intitalization\n"));
	if (!threads_init(&monitor))
		return (ft_error("Error: Threads\n"));
	return (0);
}
