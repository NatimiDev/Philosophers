/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:24 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 13:58:44 by nmikuka          ###   ########.fr       */
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

// static void	cleanup_resources(t_fork *forks, int count,
// 			t_shared_config *shared_config)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		pthread_mutex_destroy(&forks[i].fork_mutex);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&shared_config->m_end_simulation);
// 	pthread_mutex_destroy(&shared_config->m_print);
// 	free(forks);
// }

void	destroy_philosophers(t_philosopher *philos, int count)
{
	int	i;

	if (!philos)
		return;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].m_meal_time);
		pthread_mutex_destroy(&philos[i].m_status);
		i++;
	}
	free(philos);
}

static void destroy_forks(t_fork *forks, int count)
{
	int	i;

	if (!forks)
		return;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i].fork_mutex);
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
