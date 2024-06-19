/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 13:40:44 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/04 17:04:57 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->print_lock);
	if (!death_loop(philo))
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
			action);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	print_action(philo, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->time_to_die);
		return (ptr_philo);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!death_loop(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (ptr_philo);
}
