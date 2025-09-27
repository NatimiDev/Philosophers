/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:39:54 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/13 21:13:18 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (simulation_has_ended(philo->shared_config))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (false);
	}
	safe_printf(philo->shared_config, philo->config.start_time, philo->id,
		"has taken a fork");
	pthread_mutex_lock(philo->second_fork);
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
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}
