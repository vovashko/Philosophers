/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 16:04:35 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/03/28 13:31:31 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_dinner *dinner, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	if (pthread_create(&monitor_thread, NULL, &monitor, dinner->philo))
		destroy_mutexes(forks, dinner);
	while (i < dinner->philo[0].num_of_philos)
	{
		if (pthread_create(&dinner->philo[i].thread, NULL, &philo_routine,
				&dinner->philo[i]))
			destroy_mutexes(forks, dinner);
		i++;
	}
	i = 0;
	if (pthread_join(monitor_thread, NULL))
		destroy_mutexes(forks, dinner);
	while (i < dinner->philo[0].num_of_philos)
	{
		if (pthread_join(dinner->philo[i].thread, NULL))
			destroy_mutexes(forks, dinner);
		i++;
	}
	return (0);
}

void	destroy_mutexes(pthread_mutex_t *forks, t_dinner *dinner)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&dinner->dead_lock);
	pthread_mutex_destroy(&dinner->eat_lock);
	pthread_mutex_destroy(&dinner->print_lock);
	while (i < dinner->philo[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
