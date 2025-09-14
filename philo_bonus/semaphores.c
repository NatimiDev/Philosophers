/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:08:22 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/14 17:23:32 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_semaphores(t_semaphores *sems, int philosopher_count)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	
	sems->sem_forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, philosopher_count);
	if (sems->sem_forks == SEM_FAILED)
	{
		ft_perror("sem_open forks");
		return (0);
	}
	sems->sem_death = sem_open("/death", O_CREAT | O_EXCL, 0644, 1);
	if (sems->sem_death == SEM_FAILED)
	{
		ft_perror("sem_open death");
		sem_close(sems->sem_forks);
		sem_unlink("/forks");
		return (0);
	}
	return (1);
}

void	cleanup_semaphores(t_semaphores *sems)
{
	if (sems->sem_forks != SEM_FAILED)
	{
		sem_close(sems->sem_forks);
		sem_unlink("/forks");
	}
	if (sems->sem_death != SEM_FAILED)
	{
		sem_close(sems->sem_death);
		sem_unlink("/death");
	}
}

void	log_status(t_philosopher philo, const char *message, sem_t *sem_death)
{
	long	start_time;

	start_time = philo.config.start_time;
	sem_wait(sem_death);
	printf("%ld %d %s\n", get_time_since_start(start_time), philo.id, message);
	sem_post(sem_death);
}
