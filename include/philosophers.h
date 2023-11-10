/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:14:06 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 19:20:20 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define RESET_COLOR "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_simulation	*sim;
}				t_philosopher;

typedef struct s_simulation
{
	int				miam;
	int				is_simulation_running;
	int				all_philosophers_have_eaten;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_count_meal;
	pthread_mutex_t	mutex_finish_meal;
	pthread_mutex_t	mutex_print;
	pthread_t		*thread;
	int				philo_is_dead;
	int				philosopher_count;
	long			time_until_death;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				required_meals_count;
	int				simulation_start_time;
	t_philosopher	*philosophers;
}				t_simulation;

/*  actions */
void	forked(t_philosopher *philo);
void	drop_forks(pthread_mutex_t *philo);

/*  philo_actions */
void	take_forks(pthread_mutex_t *fork, t_philosopher *philo);
int		eat(t_philosopher *philo);
int		think(t_philosopher *philo);
int		sleep_philo(t_philosopher *philo);

/*  parsing */
int		parse_arguments(int argc, char **argv, t_simulation *sim);
int		parse_is_num(char **argv);
int		check_arg(int argc, char **argv, t_simulation *sim);

/*  thread */
void	run_simulation(t_simulation *sim);
void	join_philosopher_threads(t_simulation *sim, pthread_t *monitor);
void	create_philosopher_threads(t_simulation *sim, pthread_t *monitor);

/* display */
void	*philosopher_routine(void *arg);
void	display_philo_status(t_philosopher *philo, char *status);
void	*monitor_check(void *arg);

/*  died_verif */
int		check_death(t_philosopher *philo);
void	display_died(t_philosopher *philo);

/*  utils */
void	ft_usleep(int duration);
int		ft_atoi(const char *str);
void	ft_putstr(char *s);
int		get_current_time(void);
void	free_resources(t_simulation *data);

/*  init */
int		init_simulation(t_simulation *sim);
void	init_global_mutexes(t_simulation *sim);
int		clean_resources(t_simulation *sim, int step);

#endif