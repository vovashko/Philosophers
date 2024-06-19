/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 16:04:31 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/05 13:28:53 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_dinner(t_dinner *dinner, char **argv)
{
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Philos can't be more than 200\n");
		exit(1);
	}
	dinner->num_of_philos = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		dinner->meals_to_eat = ft_atoi(argv[5]);
	else
		dinner->meals_to_eat = -1;
	init_semaphores(dinner);
}

void	init_semaphores(t_dinner *dinner)
{
	sem_unlink("/forks_sem");
	dinner->forks_sem = sem_open("/forks_sem", O_CREAT, 0644,
			dinner->num_of_philos);
	sem_unlink("/print_sem");
	dinner->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	sem_unlink("/eat_sem");
	dinner->eat_sem = sem_open("/eat_sem", O_CREAT, 0644, 1);
	sem_unlink("/full_sem");
	dinner->full_sem = sem_open("/full_sem", O_CREAT, 0644, 1);
	if (dinner->forks_sem == SEM_FAILED || dinner->print_sem == SEM_FAILED
		|| dinner->eat_sem == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(1);
	}
}

void	init_philos(t_philo *philo, t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].dinner = dinner;
		sem_unlink("/dead_sem");
		philo[i].dead_sem = sem_open("/is_dead", O_CREAT, 0644, 1);
		if (philo[i].dead_sem == SEM_FAILED)
		{
			printf("Error: sem_open failed\n");
			exit(1);
		}
		i++;
	}
}
