/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:37:01 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/26 21:42:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	compute_start_delay(t_philo_config config, int id);
static int	is_philosopher_full(t_philosopher philo);

long	get_last_meal_time(t_philosopher *philo)
{
	long	last_meal_time;

	sem_wait(philo->sem_meal_time);
	last_meal_time = philo->last_meal_time;
	sem_post(philo->sem_meal_time);
	return (last_meal_time);
}

void	*run_monitor(void *arg)
{
	t_philosopher	*philo;
	int				time_to_die;

	philo = (t_philosopher *) arg;
	time_to_die = philo->config.time_to_die;
	while (true)
	{
		if (get_time_since_start(get_last_meal_time(philo)) >= time_to_die)
		{
			sem_wait(philo->sem_death);
			printf("%ld %d died\n",
				get_time_since_start(philo->config.start_time), philo->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_philosopher(int i, t_philo_config config, t_semaphores *sems)
{
	t_philosopher	philo;
	pthread_t		death_monitor;

	philo.id = i + 1;
	philo.meals_eaten = 0;
	philo.last_meal_time = config.start_time;
	philo.config = config;
	philo.sem_death = sems->sem_death;
	philo.sem_meal_time = sems->sem_meal_time[i];
	pthread_create(&death_monitor, NULL, run_monitor, &philo);
	pthread_detach(death_monitor);
	log_status(philo, "is thinking");
	precise_sleep(compute_start_delay(config, philo.id));
	while (true)
	{
		take_forks(philo, config, sems->sem_forks);
		eat(&philo, config);
		put_forks(sems->sem_forks);
		if (is_philosopher_full(philo))
			exit(0);
		sleep_and_think(philo, config);
	}
}

static int	is_philosopher_full(t_philosopher philo)
{
	int	meals_required;

	meals_required = philo.config.meals_required_per_philosopher;
	return (meals_required > 0 && philo.meals_eaten >= meals_required);
}

static int	compute_start_delay(t_philo_config config, int id)
{
	int	n;

	n = config.philosopher_count;
	if (n % 2 == 1 && id == n)
		return (2 * config.time_to_eat);
	return ((id > n / 2) * config.time_to_eat);
}
