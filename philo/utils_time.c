/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:37:13 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/14 17:01:08 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_curr_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_perror("ERROR: cannot get current time");
	return ((long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_time_since_start(long start_time)
{
	return (get_curr_time_in_ms() - start_time);
}

int	precise_sleep(t_philosopher *philo, int target_duration)
{
	long	start_time;

	start_time = get_curr_time_in_ms();
	if (target_duration <= 0)
		return (1);
	while (get_time_since_start(start_time) < target_duration)
	{
		if (simulation_has_ended(philo->shared_config))
			return (0);
		usleep(500);
	}
	return (1);
}
