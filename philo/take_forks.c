/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:39:54 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 13:13:57 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	run(t_philo_config config)
// {
// 	int				i;
// 	t_shared_config	shared_config;
// 	t_fork			forks[config.philosopher_count];
// 	pthread_t		threads[config.philosopher_count];
// 	t_philosopher	philos[config.philosopher_count];
// 	pthread_t		monitor_thread;
// 	void			*func;

// 	func = get_philosopher_function(config);
// 	pthread_mutex_init(&shared_config.m_end_simulation, NULL);
// 	shared_config.should_end_simulation = false;
// 	pthread_mutex_init(&shared_config.m_print, NULL);
// 	shared_config.msg_printed = false;
// 	i = 0;
// 	while (i < config.philosopher_count)
// 	{
// 		pthread_mutex_init(&forks[i].fork_mutex, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < config.philosopher_count)
// 	{
// 		philos[i] = create_philosopher(i + 1, forks, config, &shared_config);
// 		i++;
// 	}
// 	config.start_time = get_curr_time_in_ms();
// 	i = 0;
// 	while (i < config.philosopher_count)
// 	{
// 		if (pthread_create(&threads[i], NULL, func, &philos[i]) != 0)
// 		{
// 			perror("Failed to create thread");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	pthread_create(&monitor_thread, NULL, death_monitor, philos);
// 	pthread_join(monitor_thread, NULL);
// 	i = 0;
// 	while (i < config.philosopher_count)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < config.philosopher_count)
// 	{
// 		pthread_mutex_destroy(&forks[i].fork_mutex);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&shared_config.m_end_simulation);
// 	pthread_mutex_destroy(&shared_config.m_print);
// 	return (0);
// }

bool	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	if (simulation_has_ended(philo->shared_config))
	{
		pthread_mutex_unlock(&philo->first_fork->fork_mutex);
		return (false);
	}
	safe_printf(philo->shared_config, philo->config.start_time, philo->id,
		"has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	if (simulation_has_ended(philo->shared_config))
	{
		put_down_forks(philo);
		return (false);
	}
	safe_printf(philo->shared_config, philo->config.start_time, philo->id,
		"has taken a fork");
	return (true);
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
}
