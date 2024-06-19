/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 18:05:50 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/05 13:29:31 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo		philo[PHILO_MAX];
	t_dinner	dinner;

	if (check_args(argc, argv))
		return (1);
	init_dinner(&dinner, argv);
	init_philos(philo, &dinner);
	launch_processes(philo);
	destroy_semaphores(philo);
	return (0);
}
