/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:34 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 19:32:01 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if(philo->sim->all_philosophers_have_eaten)
			break ;
		if (think(philo))
			break ;
		else if (eat(philo))
			break ;
		else if (sleep_philo(philo))
			break ;
		pthread_mutex_lock(&philo->sim->mutex_count_meal);
		if (philo->sim->required_meals_count != -1
			&& philo->meals_eaten >= philo->sim->required_meals_count)
		{
			pthread_mutex_lock(&philo->sim->mutex_finish_meal);
			philo->sim->all_philosophers_have_eaten = 1;
			pthread_mutex_unlock(&philo->sim->mutex_finish_meal);
			pthread_mutex_unlock(&philo->sim->mutex_count_meal);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->mutex_count_meal);
	}
	return (NULL);
}

void	*monitor_check(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (philo->sim->all_philosophers_have_eaten)
			break ;
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (philo->sim->philo_is_dead >= 1)
		{
			pthread_mutex_unlock(&philo->sim->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);
		if (check_death(philo))
		{
			pthread_mutex_lock(&philo->sim->mutex_last_meal);
			if (philo->sim->all_philosophers_have_eaten == 0)
				display_died(philo);
			pthread_mutex_unlock(&philo->sim->mutex_last_meal);
			return (NULL);
		}
	}
	return (NULL);
}

char	*get_status_color(char *status)
{
	if (!strcmp(status, "is eating"))
		return (GREEN);
	if (!strcmp(status, "is sleeping"))
		return (YELLOW);
	if (!strcmp(status, "is thinking"))
		return (BLUE);
	if (!strcmp(status, "has taken a fork"))
		return (MAGENTA);
	return (RESET);
}

void	display_philo_status(t_philosopher *philo, char *status)
{
	int		time;
	char	*color_code;

	time = get_current_time() - philo->sim->simulation_start_time;
	color_code = get_status_color(status);
	pthread_mutex_lock(&philo->sim->mutex_print);
	if (philo->sim->philo_is_dead < 1)
	{
		printf("%s[%d] %d %s\033[0m\n", color_code, time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->sim->mutex_print);
}
