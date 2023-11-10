/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:17:52 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:19:00 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&mutexes[i], 0) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&mutexes[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	init_global_mutexes(t_simulation *sim)
{
	pthread_mutex_init(&sim->death_mutex, 0);
	pthread_mutex_init(&sim->mutex_last_meal, 0);
	pthread_mutex_init(&sim->mutex_count_meal, 0);
	pthread_mutex_init(&sim->mutex_finish_meal, 0);
	pthread_mutex_init(&sim->mutex_print, 0);
	sim->philo_is_dead = 0;
	sim->all_philosophers_have_eaten = 0;
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philosopher_count)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].last_meal_time = get_current_time();
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].left_fork = &sim->forks_mutex[i];
		sim->philosophers[i].right_fork = &sim->forks_mutex[(i + 1)
			% sim->philosopher_count];
		i++;
	}
	init_global_mutexes(sim);
	return (0);
}

int	init_simulation(t_simulation *sim)
{
	pthread_mutex_t	*new_forks;
	t_philosopher	*new_philos;
	pthread_t		*new_threads;

	new_forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!new_forks)
		return (-1);
	if (init_mutexes(new_forks, sim->philosopher_count) == -1)
		return (clean_resources(sim, 1));
	new_philos = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	if (!new_philos)
		return (clean_resources(sim, 2));
	new_threads = malloc(sizeof(pthread_t) * sim->philosopher_count);
	if (!new_threads)
		return (clean_resources(sim, 3));
	sim->forks_mutex = new_forks;
	sim->philosophers = new_philos;
	sim->thread = new_threads;
	return (init_philosophers(sim));
}

int	clean_resources(t_simulation *sim, int step)
{
	int	i;

	i = sim->philosopher_count;
	if (step > 2)
		free(sim->philosophers);
	if (step > 1)
	{
		while (i-- > 0)
			pthread_mutex_destroy(&sim->forks_mutex[i]);
		free(sim->forks_mutex);
	}
	if (step > 0)
		free(sim->thread);
	return (-1);
}
