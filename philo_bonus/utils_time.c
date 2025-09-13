/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:37:13 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 21:59:04 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_curr_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_time_since_start(long start_time)
{
	return (get_curr_time_in_ms() - start_time);
}

int	precise_sleep(t_philosopher philo, int target_duration, sem_t *sem_death)
{
	long	start_time;
	long	start_sim_time;
	int		time_to_die;

	start_time = get_curr_time_in_ms();
	start_sim_time = philo.config.start_time;
	time_to_die = philo.config.time_to_die;
	if (target_duration <= 0)
		return (1);
	while (get_time_since_start(start_time) < target_duration)
	{
		if (get_time_since_start(philo.last_meal_time) >= time_to_die)
		{
			sem_wait(sem_death);
			printf("%ld %d died\n", get_time_since_start(start_sim_time),
				philo.id);
			exit(1);
		}
		usleep(500);
	}
	return (1);
}
