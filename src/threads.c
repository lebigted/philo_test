/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:37:20 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:27:02 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	join_philosopher_threads(t_simulation *sim, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < sim->philosopher_count)
	{
		pthread_join(sim->thread[i], NULL);
		pthread_join(monitor[i], NULL);
	}
}

void	create_philosopher_threads(t_simulation *sim, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < sim->philosopher_count)
	{
		pthread_create(&sim->thread[i], NULL, philosopher_routine,
			&sim->philosophers[i]);
		pthread_create(&monitor[i], NULL, monitor_check, &sim->philosophers[i]);
	}
}

void	run_simulation(t_simulation *sim)
{
	pthread_t	*monitor;

	monitor = malloc(sizeof(pthread_t) * sim->philosopher_count);
	if (!monitor)
	{
		exit(EXIT_FAILURE);
	}
	create_philosopher_threads(sim, monitor);
	join_philosopher_threads(sim, monitor);
	free(monitor);
}
