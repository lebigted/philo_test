/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:45:01 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:24:55 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->philo_is_dead)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	forked(philo);
	pthread_mutex_lock(&philo->sim->mutex_last_meal);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->sim->mutex_last_meal);
	display_philo_status(philo, "is eating");
	ft_usleep(philo->sim->time_to_eat);
	pthread_mutex_lock(&philo->sim->mutex_count_meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->mutex_count_meal);
	drop_forks(philo->left_fork);
	drop_forks(philo->right_fork);
	return (0);
}

int	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->philo_is_dead >= 1)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	display_philo_status(philo, "is thinking");
	return (0);
}

int	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->philo_is_dead >= 1)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	display_philo_status(philo, "is sleeping");
	ft_usleep(philo->sim->time_to_sleep);
	return (0);
}
