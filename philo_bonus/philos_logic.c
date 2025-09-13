/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:37:01 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/13 12:08:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	compute_start_delay(t_philo_config config, int id);
static int	is_philosopher_full(t_philosopher philo);

void	create_philosopher(int id, t_philo_config config, sem_t *sem_forks,
			sem_t *sem_death)
{
	t_philosopher	philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = config.start_time;
	philo.config = config;
	log_status(philo, "is thinking", sem_death);
	precise_sleep(philo, compute_start_delay(config, id), sem_death);
	while (1)
	{
		take_forks(philo, config, sem_forks, sem_death);
		eat(&philo, config, sem_death);
		put_forks(sem_forks);
		if (is_philosopher_full(philo))
			exit(0);
		sleep_and_think(philo, config, sem_death);
	}
}

static int	is_philosopher_full(t_philosopher philo)
{
	int	meals_required;

	meals_required = philo.config.meals_required_per_philosopher;
	return (meals_required > 0 && philo.meals_eaten >= meals_required);
}

// static int	compute_start_delay(t_philo_config config, int id)
// {
// 	int	n;

// 	n = config.philosopher_count;
// 	if (n % 2 == 1 && id == n)
// 		return (2 * config.time_to_eat);
// 	// return ((id - 1) % 2 * config.time_to_eat);
// 	return ((id > n / 2) * config.time_to_eat);
// }

static int	compute_start_delay(t_philo_config config, int id)
{
	int	variation_delay;
	int	n;

	n = config.philosopher_count;
	if (n % 2 == 0)
		return ((id - 1) % 2 * config.time_to_eat);
	if (id <= 3)
		return ((id - 1) % 3 * config.time_to_eat);
	variation_delay = (n - id + 2) * config.time_to_eat / n;
	return (id % 2 * config.time_to_eat + variation_delay);
}
