/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 13:40:44 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/05 13:32:18 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, char *action)
{
	sem_wait(philo->dinner->print_sem);
	printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
		action);
	sem_post(philo->dinner->print_sem);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->dinner->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->dinner->forks_sem);
	print_action(philo, "has taken a fork");
	sem_wait(philo->dinner->forks_sem);
	print_action(philo, "has taken a fork");
	philo->eating = 1;
	print_action(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->dinner->eat_sem);
	sem_post(philo->dead_sem);
	ft_usleep(philo->dinner->time_to_eat);
	philo->eating = 0;
	sem_post(philo->dinner->forks_sem);
	sem_post(philo->dinner->forks_sem);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		if (philo->meals_eaten >= philo->dinner->meals_to_eat
			&& philo->dinner->meals_to_eat != -1)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
