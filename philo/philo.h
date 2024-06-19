/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vshkonda <vshkonda@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 13:40:53 by vshkonda      #+#    #+#                 */
/*   Updated: 2024/04/05 13:35:40 by vshkonda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_of_philos;
	int				meals_eaten;
	size_t			last_meal;
	int				meals_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				*is_dead;
	int				eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_dinner
{
	t_philo			*philo;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	print_lock;
	int				is_dead;
}					t_dinner;

// init.c
void				init_philos(t_philo *philo, t_dinner *dinner,
						pthread_mutex_t *forks, char **argv);
void				init_input(t_philo *philo, char **argv);
void				init_forks(pthread_mutex_t *forks, int num_of_philos);
void				init_dinner(t_dinner *dinner, t_philo *philo);

// routine.c
void				print_action(t_philo *philo, char *action);
void				philo_think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);
void				*philo_routine(void *ptr_philo);

// monitor.c
void				*monitor(void *ptr_philo);
int					death_loop(t_philo *philo);
int					check_if_any_died(t_philo *philo);
int					check_if_all_full(t_philo *philo);

// utils.c
int					check_args(int argc, char **argv);
int					ft_isdigit(char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t ms);
int					ft_atoi(char *str);

// threads.c
int					launch_threads(t_dinner *dinner, pthread_mutex_t *forks);
void				destroy_mutexes(pthread_mutex_t *forks, t_dinner *dinner);
