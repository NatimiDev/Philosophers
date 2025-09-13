/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:06:55 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/12 14:37:58 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

t_philo_config	init_config(int argc, char *argv[]);
int				init_shared_config(t_shared_config *shared_config);
pthread_mutex_t	*init_forks(int count);
t_philosopher	*init_philosophers(t_philo_config config, pthread_mutex_t *forks,
					t_shared_config *shared_config);
int				init_simulation(t_philo_config config, t_philo_data *data);

t_philosopher	create_philosopher(int id, pthread_mutex_t *forks,
					t_philo_config config, t_shared_config *shared_config);

int				run(t_philo_config config);

void			wait_for_threads(pthread_t *threads, pthread_t monitor_thread,
					int count);
void			cleanup_simulation(t_philo_data *data, int count);

void			*philosopher_one(void *arg);
void			*philosopher(void *arg);

bool			take_forks(t_philosopher *philo);
void			put_down_forks(t_philosopher *philo);

void			*death_monitor(void *arg);
int				simulation_has_ended(t_shared_config *config);

// safe set, get and print functions that use mutex to protect write and read
void			safe_printf(t_shared_config *config, long start_time, int id,
					const char *action);
void			set_last_meal_time(t_philosopher *philo);
long			get_last_meal_time(t_philosopher *philo);
bool			check_and_increment_meals(t_philosopher *philo);
bool			get_status(t_philosopher *philo);

// helper functions
bool			ft_isnumeric(char *str);
int				ft_atoi(const char *str);
void			ft_perror(char *s);

long			get_curr_time_in_ms(void);
long			get_time_since_start(long start_time);
int				precise_sleep(t_philosopher *philo, int target_duration);

#endif
