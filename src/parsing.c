/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:31:04 by ltestard          #+#    #+#             */
/*   Updated: 2023/11/10 12:23:34 by ltestard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_arg(int argc, char **argv, t_simulation *sim)
{
	if (parse_arguments(argc, argv, sim) != 0)
	{
		printf("Erreur : arguments invalides.\n");
		return (1);
	}
	if (init_simulation(sim) != 0)
	{
		printf("Erreur : échec de l'initialisation.\n");
		return (1);
	}
	return (0);
}

int	parse_is_num(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!(argv[j][i] <= '9' && argv[j][i] >= '0'))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (parse_is_num(argv))
		return (-1);
	sim->philosopher_count = atoi(argv[1]);
	sim->time_to_die = atoi(argv[2]);
	sim->time_to_eat = atoi(argv[3]);
	sim->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		sim->required_meals_count = atoi(argv[5]);
	else
		sim->required_meals_count = -1;
	if (sim->philosopher_count <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| (argc == 6 && sim->required_meals_count <= 0))
		return (-1);
	return (0);
}
