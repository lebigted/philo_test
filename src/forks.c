/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:42:21 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:10:27 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_forks(pthread_mutex_t *fork, t_philosopher *philo)
{
	pthread_mutex_lock(fork);
	display_philo_status(philo, "has taken a fork");
}

void	drop_forks(pthread_mutex_t *philo)
{
	pthread_mutex_unlock(philo);
}

void	forked(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		take_forks(philo->left_fork, philo);
		take_forks(philo->right_fork, philo);
	}
	else
	{
		take_forks(philo->right_fork, philo);
		take_forks(philo->left_fork, philo);
	}
}
