/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:37:01 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/13 21:39:29 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating_cycle(t_philosopher *philo);
static int	sleeping_cycle(t_philosopher *philo);
static int	thinking_cycle(t_philosopher *philo);

void	*philosopher_one(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (simulation_has_ended(philo->shared_config))
		return (NULL);
	set_last_meal_time(philo);
	safe_printf(philo->shared_config, philo->config.start_time,
		philo->id, "is thinking");
	pthread_mutex_lock(philo->first_fork);
	safe_printf(philo->shared_config, philo->config.start_time, philo->id,
		"has taken a fork");
	precise_sleep(philo, philo->config.time_to_die * 1000);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	set_last_meal_time(philo);
	safe_printf(philo->shared_config, philo->config.start_time,
		philo->id, "is thinking");
	if (philo->start_delay > 0 && !precise_sleep(philo, philo->start_delay))
		return (NULL);
	while (!simulation_has_ended(philo->shared_config))
	{
		if (!eating_cycle(philo))
			break ;
		if (check_and_increment_meals(philo))
			break ;
		if (!sleeping_cycle(philo))
			break ;
		if (!thinking_cycle(philo))
			break ;
	}
	return (NULL);
}

static int	eating_cycle(t_philosopher *philo)
{
	if (!take_forks(philo))
		return (0);
	set_last_meal_time(philo);
	safe_printf(philo->shared_config, philo->config.start_time,
		philo->id, "is eating");
	if (!precise_sleep(philo, philo->config.time_to_eat))
	{
		put_down_forks(philo);
		return (0);
	}
	put_down_forks(philo);
	return (1);
}

static int	sleeping_cycle(t_philosopher *philo)
{
	safe_printf(philo->shared_config, philo->config.start_time,
		philo->id, "is sleeping");
	return (precise_sleep(philo, philo->config.time_to_sleep));
}

static int	thinking_cycle(t_philosopher *philo)
{
	safe_printf(philo->shared_config, philo->config.start_time,
		philo->id, "is thinking");
	precise_sleep(philo,
		philo->config.time_to_eat - philo->config.time_to_sleep);
	if (philo->config.philosopher_count == 3)
		precise_sleep(philo, philo->config.time_to_eat / 4);
	return (1);
}
