/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:36:57 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 10:59:22 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_config	config;

	if (argc < 5)
	{
		ft_perror("Invalid input.");
		return (1);
	}
	config = init_config(argc, argv);
	if (config.philosopher_count <= 0 || config.time_to_die < 0
		|| config.time_to_eat < 0 || config.time_to_sleep < 0
		|| (argc > 5 && config.meals_required_per_philosopher <= 0))
	{
		ft_perror("Invalid input.");
		return (1);
	}
	return (run(config));
}

t_philo_config	init_config(int argc, char *argv[])
{
	t_philo_config	config;

	config.philosopher_count = -1;
	config.time_to_die = -1;
	config.time_to_eat = -1;
	config.time_to_sleep = -1;
	config.meals_required_per_philosopher = -1;
	if (!ft_isnumeric(argv[1]) || !ft_isnumeric(argv[2])
		|| !ft_isnumeric(argv[3]) || !ft_isnumeric(argv[4])
		|| (argc > 5 && !ft_isnumeric(argv[5])))
		return (config);
	config.philosopher_count = ft_atoi(argv[1]);
	config.time_to_die = ft_atoi(argv[2]);
	config.time_to_eat = ft_atoi(argv[3]);
	config.time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		config.meals_required_per_philosopher = ft_atoi(argv[5]);
	config.start_time = get_curr_time_in_ms();
	return (config);
}
