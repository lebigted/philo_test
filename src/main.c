/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:14:10 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:51:59 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	single_philosopher_routine(t_simulation *sim)
{
	pthread_mutex_lock(&sim->death_mutex);
	printf("[0] 1 is thinking\n");
	printf("[%ld] 1 has taken a fork\n", sim->time_to_die);
	usleep(sim->time_to_die);
	printf("[%ld] 1 is dead\n", sim->time_to_die);
	pthread_mutex_unlock(&sim->death_mutex);
	free_resources(sim);
}

void	free_resources(t_simulation *data)
{
	int	i;

	if (data->forks_mutex)
	{
		i = 0;
		while (i < data->philosopher_count)
		{
			pthread_mutex_destroy(&data->forks_mutex[i]);
			i++;
		}
		free(data->forks_mutex);
	}
	if (data->philosophers)
		free(data->philosophers);
	if (data->thread)
		free(data->thread);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->mutex_last_meal);
	pthread_mutex_destroy(&data->mutex_count_meal);
	pthread_mutex_destroy(&data->mutex_finish_meal);
	pthread_mutex_destroy(&data->mutex_print);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (check_arg(argc, argv, &sim))
		return (1);
	sim.simulation_start_time = get_current_time();
	if (sim.philosopher_count == 1)
	{
		single_philosopher_routine(&sim);
	}
	else
	{
		run_simulation(&sim);
	}
	free_resources(&sim);
	return (0);
}
