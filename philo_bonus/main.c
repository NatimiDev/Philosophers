/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:36:57 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/26 21:46:51 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_config(int argc, char *argv[], t_philo_config *config);

int	main(int argc, char *argv[])
{
	t_philo_config	config;

	if (argc != 5 && argc != 6)
	{
		ft_perror("Invalid number of arguments.");
		return (1);
	}
	if (!init_config(argc, argv, &config))
	{
		ft_perror("Invalid input. Only positive numbers are allowed.");
		return (1);
	}
	if (config.philosopher_count == 0)
	{
		printf("No philosopher to create.");
		return (0);
	}
	if (config.meals_required_per_philosopher == 0)
	{
		printf("All philosophers are satisfied. No one is hungry.");
		return (0);
	}
	return (run(config));
}

static bool	init_config(int argc, char *argv[], t_philo_config *config)
{
	if (!ft_is_natural_number(argv[1]) || !ft_is_natural_number(argv[2])
		|| !ft_is_natural_number(argv[3]) || !ft_is_natural_number(argv[4])
		|| (argc > 5 && !ft_is_natural_number(argv[5])))
		return (NULL);
	config->philosopher_count = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->meals_required_per_philosopher = -1;
	if (argc > 5)
		config->meals_required_per_philosopher = ft_atoi(argv[5]);
	config->start_time = get_curr_time_in_ms();
	return (config);
}
