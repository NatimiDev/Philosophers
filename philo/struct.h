/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:13:21 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/12 14:42:20 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <pthread.h>

typedef struct s_philo_config
{
	int		philosopher_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_required_per_philosopher;
	long	start_time;
}	t_philo_config;

typedef struct s_shared_config
{
	bool			should_end_simulation;
	pthread_mutex_t	m_end_simulation;
	bool			msg_printed;
	pthread_mutex_t	m_print;
}	t_shared_config;

typedef struct s_philosopher
{
	int				start_delay;
	int				id;
	int				meals_eaten;
	bool			is_full;
	pthread_mutex_t	m_status;
	long			last_meal_time;
	pthread_mutex_t	m_meal_time;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	t_philo_config	config;
	t_shared_config	*shared_config;
}	t_philosopher;

typedef struct s_philo_data
{
	t_shared_config	shared_config;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philosopher	*philos;
}	t_philo_data;

#endif