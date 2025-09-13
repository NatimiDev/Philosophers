/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:24 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/12 14:47:07 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_threads(pthread_t *threads, pthread_t monitor_thread,
			int count)
{
	int	i;

	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	destroy_philosophers(t_philosopher *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].m_meal_time);
		pthread_mutex_destroy(&philos[i].m_status);
		i++;
	}
	free(philos);
}

static void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	cleanup_simulation(t_philo_data *data, int count)
{
	destroy_forks(data->forks, count);
	destroy_philosophers(data->philos, count);
	pthread_mutex_destroy(&data->shared_config.m_end_simulation);
	pthread_mutex_destroy(&data->shared_config.m_print);
	free(data->threads);
}
