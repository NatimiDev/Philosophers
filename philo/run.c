/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:31 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 13:40:13 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_philosopher *philos, pthread_t *threads,
				t_philo_config *config);
static void	*get_philosopher_function(t_philo_config config);
static int	compute_start_delay(t_philo_config config, int id);

int	run(t_philo_config config)
{
	t_philo_data	data;
	pthread_t		monitor;

	if (!init_simulation(config, &data))
	{
		cleanup_simulation(&data, config.philosopher_count);
		return (1);
	}
	if (!start_threads(data.philos, data.threads, &config))
	{
		cleanup_simulation(&data, config.philosopher_count);
		return (1);
	}
	if (pthread_create(&monitor, NULL, death_monitor, data.philos) != 0)
	{
		wait_for_threads(data.threads, monitor, config.philosopher_count);
		cleanup_simulation(&data, config.philosopher_count);
		return (1);
	}
	wait_for_threads(data.threads, monitor, config.philosopher_count);
	cleanup_simulation(&data, config.philosopher_count);
	return (0);
}

static int	start_threads(t_philosopher *philos, pthread_t *threads,
						t_philo_config *config)
{
	void	*func;
	int		i;

	func = get_philosopher_function(*config);
	config->start_time = get_curr_time_in_ms();
	i = 0;
	while (i < config->philosopher_count)
	{
		if (pthread_create(&threads[i], NULL, func, &philos[i]) != 0)
		{
			ft_perror("Failed to create thread");
			return (0);
		}
		i++;
	}
	return (1);
}

static void	*get_philosopher_function(t_philo_config config)
{
	if (config.philosopher_count == 1)
		return (philosopher_one);
	return (philosopher);
}

t_philosopher	create_philosopher(int id, t_fork *forks,
							t_philo_config config,
							t_shared_config *shared_config)
{
	t_philosopher	new_philo;
	t_fork			*right_fork;
	t_fork			*left_fork;

	new_philo.id = id;
	right_fork = &forks[id - 1];
	left_fork = &forks[id % config.philosopher_count];
	if (id % 2)
	{
		new_philo.first_fork = left_fork;
		new_philo.second_fork = right_fork;
	}
	else
	{
		new_philo.first_fork = right_fork;
		new_philo.second_fork = left_fork;
	}
	new_philo.meals_eaten = 0;
	new_philo.is_full = false;
	new_philo.last_meal_time = get_curr_time_in_ms();
	new_philo.config = config;
	new_philo.shared_config = shared_config;
	pthread_mutex_init(&new_philo.m_meal_time, NULL);
	pthread_mutex_init(&new_philo.m_status, NULL);
	new_philo.start_delay = compute_start_delay(config, id);
	return (new_philo);
}

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
