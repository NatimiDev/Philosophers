/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:47:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 14:01:42 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_printf(t_shared_config *config, long start_time, int id,
			const char *msg)
{
	pthread_mutex_lock(&config->m_print);
	if (!config->should_end_simulation)
		printf("%li %d %s\n", get_time_since_start(start_time), id, msg);
	pthread_mutex_unlock(&config->m_print);
}

long	get_last_meal_time(t_philosopher *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->m_meal_time);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->m_meal_time);
	return (last_meal_time);
}

void	set_last_meal_time(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->m_meal_time);
	philo->last_meal_time = get_curr_time_in_ms();
	pthread_mutex_unlock(&philo->m_meal_time);
}

bool	get_status(t_philosopher *philo)
{
	bool	is_full;

	pthread_mutex_lock(&philo->m_status);
	is_full = philo->is_full;
	pthread_mutex_unlock(&philo->m_status);
	return (is_full);
}

// void	set_status(t_philosopher *philo)
// {
// 	pthread_mutex_lock(&philo->m_meal_time);
// 	philo->is_full = true;
// 	pthread_mutex_unlock(&philo->m_meal_time);
// }

bool	check_and_increment_meals(t_philosopher *philo)
{
	bool	is_full;
	int		meals_required;

	meals_required = philo->config.meals_required_per_philosopher;
	pthread_mutex_lock(&philo->m_status);
	philo->meals_eaten++;
	is_full = (meals_required > 0 && philo->meals_eaten >= meals_required);
	if (is_full)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->m_status);
	return (is_full);
}
