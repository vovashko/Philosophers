/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 13:40:51 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/03/28 13:34:50 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	t_dinner		dinner;
	pthread_mutex_t	forks[PHILO_MAX];

	if (check_args(argc, argv))
		return (1);
	init_dinner(&dinner, philo);
	init_input(philo, argv);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philo, &dinner, forks, argv);
	launch_threads(&dinner, forks);
	destroy_mutexes(forks, &dinner);
	return (0);
}
