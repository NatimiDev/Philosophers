/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:08:22 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/27 21:04:18 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_meal_time_sem(t_semaphores *sems, int philosopher_count);

int	init_semaphores(t_semaphores *sems, int philosopher_count)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	sems->sem_forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			philosopher_count);
	if (sems->sem_forks == SEM_FAILED)
	{
		ft_perror("ERROR: sem_open failed");
		return (0);
	}
	sem_unlink("/forks");
	sems->sem_death = sem_open("/death", O_CREAT | O_EXCL, 0644, 1);
	if (sems->sem_death == SEM_FAILED)
	{
		ft_perror("ERROR: sem_open failed");
		sem_close(sems->sem_forks);
		return (0);
	}
	sem_unlink("/death");
	init_meal_time_sem(sems, philosopher_count);
	return (1);
}

static int	init_meal_time_sem(t_semaphores *sems, int philosopher_count)
{
	int		i;
	char	sem_meal_time_name[20];

	sems->sem_meal_time = malloc(sizeof(sem_t *) * philosopher_count);
	if (!sems->sem_meal_time)
		return (1);
	i = 0;
	while (i < philosopher_count)
	{
		get_sem_name(sem_meal_time_name, i + 1);
		sems->sem_meal_time[i] = sem_open(sem_meal_time_name,
				O_CREAT | O_EXCL, 0644, 1);
		if (sems->sem_meal_time[i] == SEM_FAILED)
		{
			ft_perror("ERROR: sem_open failed");
			cleanup_semaphores(sems, i);
			return (1);
		}
		sem_unlink(sem_meal_time_name);
		i++;
	}
	return (0);
}

void	cleanup_semaphores(t_semaphores *sems, int philosopher_count)
{
	int	i;

	if (sems->sem_forks != SEM_FAILED)
		sem_close(sems->sem_forks);
	if (sems->sem_death != SEM_FAILED)
		sem_close(sems->sem_death);
	i = 0;
	while (i < philosopher_count)
	{
		if (sems->sem_meal_time[i] != SEM_FAILED)
			sem_close(sems->sem_meal_time[i]);
		i++;
	}
	free(sems->sem_meal_time);
}

void	log_status(t_philosopher philo, const char *message)
{
	long	start_time;

	start_time = philo.config.start_time;
	sem_wait(philo.sem_death);
	printf("%ld %d %s\n", get_time_since_start(start_time), philo.id, message);
	sem_post(philo.sem_death);
}
