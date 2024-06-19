/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 16:24:07 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/04 17:05:25 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_if_any_died(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	while (1)
	{
		sem_wait(philo->dead_sem);
		if (get_current_time() - philo->last_meal > philo->dinner->time_to_die
			&& philo->eating != 1)
		{
			print_action(philo, "died");
			sem_wait(philo->dinner->print_sem);
			exit(0);
		}
		sem_post(philo->dead_sem);
	}
	return (NULL);
}

void	create_philo(t_philo *philo)
{
	pthread_t	supervisor_tid;

	if (pthread_create(&supervisor_tid, NULL, check_if_any_died,
			(void *)philo) != 0)
		destroy_semaphores(philo);
	pthread_detach(supervisor_tid);
	philo_routine(philo);
	exit(0);
}
