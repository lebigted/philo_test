/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:29 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:08:58 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	display_died(t_philosopher *philo)
{
	int	timestamp;

	timestamp = get_current_time() - philo->sim->simulation_start_time;
	pthread_mutex_lock(&philo->sim->mutex_print);
	if (philo->sim->philo_is_dead == 1)
	{
		philo->sim->philo_is_dead++;
		printf("%s[%d] %d died%s\n", RED, timestamp, philo->id, RESET_COLOR);
	}
	pthread_mutex_unlock(&philo->sim->mutex_print);
}

int	check_death(t_philosopher *philo)
{
	int	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->philo_is_dead)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	pthread_mutex_lock(&philo->sim->mutex_last_meal);
	if ((current_time - philo->last_meal_time) > philo->sim->time_to_die)
	{
		philo->sim->philo_is_dead = 1;
		pthread_mutex_unlock(&philo->sim->mutex_last_meal);
		display_died(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->mutex_last_meal);
	return (0);
}
