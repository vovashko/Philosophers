/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 16:24:07 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/04 16:57:13 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	check_if_any_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo[i].eat_lock);
		if (get_current_time() - philo[i].last_meal > philo[i].time_to_die
			&& philo[i].eating != 1)
		{
			pthread_mutex_unlock(philo[i].eat_lock);
			print_action(philo, "died");
			pthread_mutex_lock(philo->dead_lock);
			*philo->is_dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philo[i].eat_lock);
		i++;
	}
	return (0);
}

int	check_if_all_full(t_philo *philo)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (philo[0].meals_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].eat_lock);
		if (philo[i].meals_eaten >= philo[i].meals_to_eat)
			full++;
		pthread_mutex_unlock(philo[i].eat_lock);
		i++;
	}
	if (full == philo->num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	while (1)
	{
		if (check_if_any_died(philo) == 1)
			break ;
		if (check_if_all_full(philo) == 1)
			break ;
	}
	return (ptr_philo);
}
