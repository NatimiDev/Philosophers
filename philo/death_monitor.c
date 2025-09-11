/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:39:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/10 13:56:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simulation(int id, t_shared_config *config, long start_time);
static bool	is_philosopher_dead(t_philosopher *philo, t_philo_config *config);

void	*death_monitor(void *arg)
{
	t_philosopher	*philos;
	t_philo_config	config;
	int				n_full;
	int				i;

	philos = (t_philosopher *)arg;
	config = philos[0].config;
	while (!simulation_has_ended(philos[0].shared_config))
	{
		n_full = 0;
		i = 0;
		while (i < config.philosopher_count)
		{
			if (get_status(&philos[i]))
				n_full++;
			else if (is_philosopher_dead(&philos[i], &config))
				return (NULL);
			i++;
		}
		if (n_full == philos[0].config.philosopher_count)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}

static bool	is_philosopher_dead(t_philosopher *philo, t_philo_config *config)
{
	if (get_time_since_start(get_last_meal_time(philo)) >= config->time_to_die)
	{
		end_simulation(philo->id, philo->shared_config, config->start_time);
		return (true);
	}
	return (false);
}

static void	end_simulation(int id, t_shared_config *config, long start_time)
{
	pthread_mutex_lock(&config->m_end_simulation);
	config->should_end_simulation = true;
	pthread_mutex_unlock(&config->m_end_simulation);
	pthread_mutex_lock(&config->m_print);
	if (!config->msg_printed)
	{
		printf("%li %d died\n", get_time_since_start(start_time), id);
		config->msg_printed = true;
	}
	pthread_mutex_unlock(&config->m_print);
}

int	simulation_has_ended(t_shared_config *config)
{
	int	simulation_ended;

	pthread_mutex_lock(&config->m_end_simulation);
	simulation_ended = config->should_end_simulation;
	pthread_mutex_unlock(&config->m_end_simulation);
	return (simulation_ended);
}
