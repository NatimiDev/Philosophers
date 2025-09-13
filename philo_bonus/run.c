/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:22:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/11 23:31:51 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pid_t	*spawn_philosophers(t_philo_config config, t_semaphores *sems);
static void		cleanup_on_fork_error(pid_t *pids, int count);
static int		wait_for_philosophers(pid_t *pids, int count);
static void		terminate_philosophers(pid_t *pids, int count, pid_t exclude);

int	run(t_philo_config config)
{
	t_semaphores	sems;
	pid_t			*pids;

	if (!init_semaphores(&sems, config.philosopher_count))
		return (1);
	pids = spawn_philosophers(config, &sems);
	if (!pids)
	{
		cleanup_semaphores(&sems);
		return (1);
	}
	wait_for_philosophers(pids, config.philosopher_count);
	free(pids);
	cleanup_semaphores(&sems);
	return (0);
}

static pid_t	*spawn_philosophers(t_philo_config config, t_semaphores *sems)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(pid_t) * config.philosopher_count);
	if (!pid)
		return (NULL);
	config.start_time = get_curr_time_in_ms();
	i = 0;
	while (i < config.philosopher_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			cleanup_on_fork_error(pid, i);
			return (NULL);
		}
		if (pid[i] == 0)
		{
			free(pid);
			create_philosopher(i + 1, config, sems->sem_forks, sems->sem_death);
			exit(0);
		}
		i++;
	}
	return (pid);
}

static void	cleanup_on_fork_error(pid_t *pids, int count)
{
	while (--count >= 0)
		kill(pids[count], SIGTERM);
	free(pids);
}

static int	wait_for_philosophers(pid_t *pids, int count)
{
	pid_t	died_pid;
	int		status;
	int		i;

	died_pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		terminate_philosophers(pids, count, died_pid);
		i = 0;
		while (i < count)
		{
			if (pids[i] != died_pid)
				waitpid(pids[i], NULL, 0);
			i++;
		}
		return (1);
	}
	i = 0;
	while (i < count)
	{
		if (pids[i] != died_pid)
			waitpid(pids[i], &status, 0);
		i++;
	}
	return (0);
}

static void	terminate_philosophers(pid_t *pids, int count, pid_t exclude)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] != exclude && pids[i] > 0)
			kill(pids[i], SIGTERM);
		i++;
	}
}
