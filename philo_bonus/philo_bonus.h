/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 18:05:45 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/04 16:35:32 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define PHILO_MAX 200

typedef struct s_dinner
{
	int			num_of_philos;
	int			meals_to_eat;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	sem_t		*print_sem;
	sem_t		*forks_sem;
	sem_t		*eat_sem;
	sem_t		*full_sem;
}				t_dinner;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			meals_eaten;
	int			eating;
	size_t		last_meal;
	size_t		start_time;
	sem_t		*dead_sem;
	t_dinner	*dinner;
}				t_philo;

// init.c
void			init_philos(t_philo *philo, t_dinner *dinner);
void			init_semaphores(t_dinner *dinner);
void			init_dinner(t_dinner *dinner, char **argv);

// monitor.c
void			*check_if_any_died(void *ptr_philo);
void			create_philo(t_philo *philo);

// routine.c
void			print_action(t_philo *philo, char *action);
void			philo_think(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_routine(t_philo *philo);

// processes.c
void			launch_processes(t_philo *philo);
void			destroy_semaphores(t_philo *philo);
void			kill_processes(t_philo *philo);

// utils.c
size_t			get_current_time(void);
int				ft_usleep(size_t ms);
int				ft_atoi(char *str);
int				ft_isdigit(char *str);
int				check_args(int argc, char **argv);
