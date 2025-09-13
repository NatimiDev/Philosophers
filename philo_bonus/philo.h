/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:06:55 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/12 23:15:37 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

t_philo_config	init_config(int argc, char *argv[]);
int				init_simulation(t_philo_config config, t_philo_data *data);

int				init_semaphores(t_semaphores *sems, int philosopher_count);
void			cleanup_semaphores(t_semaphores *sems);

void			create_philosopher(int id, t_philo_config config,
					sem_t *sem_forks, sem_t *sem_death);

int				run(t_philo_config config);

void			take_forks(t_philosopher philo, t_philo_config config,
					sem_t *sem_forks, sem_t *sem_death);
void			put_forks(sem_t *sem_forks);
void			eat(t_philosopher *philo, t_philo_config config,
					sem_t *sem_death);
void			sleep_and_think(t_philosopher philo, t_philo_config config,
					sem_t *sem_death);

void			cleanup_simulation(t_philo_data *data, int count);

// helper functions
bool			ft_isnumeric(char *str);
int				ft_atoi(const char *str);
void			ft_perror(char *s);

long			get_curr_time_in_ms(void);
long			get_time_since_start(long start_time);
int				precise_sleep(t_philosopher philo, int target_duration,
					sem_t *sem_death);

void			log_status(t_philosopher philo, const char *message,
					sem_t *sem_death);
#endif
