/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 14:36:02 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/04 17:06:00 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	launch_processes(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->dinner->num_of_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			destroy_semaphores(philo);
		if (philo[i].pid == 0)
			create_philo(&philo[i]);
		ft_usleep(1);
		i++;
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		kill_processes(philo);
}

void	destroy_semaphores(t_philo *philo)
{
	sem_close(philo->dinner->forks_sem);
	sem_unlink("/forks_sem");
	sem_close(philo->dinner->print_sem);
	sem_unlink("/print_sem");
	sem_close(philo->dinner->eat_sem);
	sem_unlink("/eat_sem");
	sem_close(philo->dead_sem);
	sem_unlink("/dead_sem");
}

void	kill_processes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->dinner->num_of_philos)
	{
		kill(philo[i].pid, SIGTERM);
		i++;
	}
}
