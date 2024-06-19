/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 16:04:31 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/05 13:36:51 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = -1;
}

void	init_philos(t_philo *philo, t_dinner *dinner, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		init_input(&philo[i], argv);
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].eating = 0;
		philo[i].is_dead = &dinner->is_dead;
		philo[i].dead_lock = &dinner->dead_lock;
		philo[i].eat_lock = &dinner->eat_lock;
		philo[i].print_lock = &dinner->print_lock;
		philo[i].left_fork = &forks[i];
		if (i == philo->num_of_philos - 1)
			philo[i].right_fork = &forks[0];
		else
			philo[i].right_fork = &forks[i + 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_dinner(t_dinner *dinner, t_philo *philo)
{
	dinner->is_dead = 0;
	dinner->philo = philo;
	pthread_mutex_init(&dinner->dead_lock, NULL);
	pthread_mutex_init(&dinner->eat_lock, NULL);
	pthread_mutex_init(&dinner->print_lock, NULL);
}
