/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:10:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/14 17:24:49 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher philo, t_philo_config config,
			sem_t *sem_forks, sem_t *sem_death)
{
	sem_wait(sem_forks);
	log_status(philo, "has taken a fork", sem_death);
	if (config.philosopher_count == 1)
	{
		precise_sleep(config.time_to_die + 1);
	}
	sem_wait(sem_forks);
	log_status(philo, "has taken a fork", sem_death);
}

void	put_forks(sem_t *sem_forks)
{
	sem_post(sem_forks);
	sem_post(sem_forks);
}

void	eat(t_philosopher *philo, t_philo_config config, sem_t *sem_death)
{
	sem_wait(philo->sem_meal_time);
	log_status(*philo, "is eating", sem_death);
	philo->last_meal_time = get_curr_time_in_ms();
	sem_post(philo->sem_meal_time);
	precise_sleep(config.time_to_eat);
	philo->meals_eaten++;
}

void	sleep_and_think(t_philosopher philo, t_philo_config config,
			sem_t *sem_death)
{
	int	middle;
	int id;

	log_status(philo, "is sleeping", sem_death);
	precise_sleep(config.time_to_sleep);
	log_status(philo, "is thinking", sem_death);
	precise_sleep(config.time_to_eat - config.time_to_sleep);
	middle = config.philosopher_count / 2;
	id = philo.id;
	if (philo.id > middle)
		id = philo.id - 1;
	// if(config.philosopher_count % 2 && (philo.id == 1 || philo.id == config.philosopher_count || philo.id == middle))
	if(config.philosopher_count % 2 && (id % middle == (philo.meals_eaten) % (middle)))
		precise_sleep(config.time_to_eat);
}
