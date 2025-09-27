/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:38:08 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/15 23:44:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int				init_shared_config(t_shared_config *shared_config);
static pthread_mutex_t	*init_forks(int count);
static t_philosopher	*init_philosophers(t_philo_config config,
							pthread_mutex_t *forks,
							t_shared_config *shared_config);

int	init_simulation(t_philo_config config, t_philo_data *data)
{
	if (!init_shared_config(&data->shared_config))
		return (0);
	data->forks = init_forks(config.philosopher_count);
	if (!data->forks)
		return (0);
	data->philos = init_philosophers(config, data->forks, &data->shared_config);
	if (!data->philos)
		return (0);
	data->threads = malloc(sizeof(pthread_t) * config.philosopher_count);
	if (!data->threads)
		return (0);
	return (1);
}

static int	init_shared_config(t_shared_config *shared_config)
{
	if (pthread_mutex_init(&shared_config->m_end_simulation, NULL) != 0)
		return (0);
	shared_config->should_end_simulation = false;
	if (pthread_mutex_init(&shared_config->m_print, NULL) != 0)
	{
		pthread_mutex_destroy(&shared_config->m_end_simulation);
		return (0);
	}
	shared_config->msg_printed = false;
	return (1);
}

static pthread_mutex_t	*init_forks(int count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&forks[i]);
			}
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_philosopher	*init_philosophers(t_philo_config config,
					pthread_mutex_t *forks, t_shared_config *shared_config)
{
	t_philosopher	*philos;
	int				i;

	philos = malloc(sizeof(t_philosopher) * config.philosopher_count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config.philosopher_count)
	{
		philos[i] = create_philosopher(i + 1, forks, config, shared_config);
		i++;
	}
	return (philos);
}
