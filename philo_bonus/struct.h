/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:13:21 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/27 00:17:50 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <semaphore.h>

typedef struct s_philo_config
{
	int		philosopher_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_required_per_philosopher;
	long	start_time;
}	t_philo_config;

typedef struct s_philosopher
{
	int						start_delay;
	int						id;
	int						meals_eaten;
	long					last_meal_time;
	t_philo_config			config;
	sem_t					*sem_death;
	sem_t					*sem_forks;
	sem_t					*sem_meal_time;
}	t_philosopher;

typedef struct s_semaphores
{
	sem_t	*sem_forks;
	sem_t	*sem_death;
	sem_t	**sem_meal_time;
}	t_semaphores;

#endif