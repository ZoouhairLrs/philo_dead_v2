/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:43:08 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 00:55:27 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died ☠️"
# define MAXINT 9999999999

// data structer
typedef struct s_argumrnts
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_must_eat;
	int				number_phil_to_eat;
	int				number_of_times_each_philosopher_must_eat;
	int				philo_is_dead;
	pthread_mutex_t	mutex_arg;
	long			time;
}	t_arguments;

// t_argument = t_input

typedef struct s_fork
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			philo_dead;
	long			last_eat;
	int				nb_eat;
	int				nbr_eat_max;
	long			new_time;
	t_fork			fork;
	t_arguments		*arguments;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_data
{
	t_arguments	*arguments;
	t_philo		*philo;
}	t_data;

// header tools
long	ft_atoi(const char *str);

// header functions
int		parsing_time(int argc, char **argv, t_data *var);
void	init_data(t_data *data, char **argv);
int		execution_part(t_data data);
t_philo	*create_philo(t_data data);
long	get_time(void);
void	manage_threads(t_philo *philo, t_data *data);
void	ft_us_sleep(unsigned int t, t_philo *philo);
int		routine_activity(t_philo *phil);
void	*routine_yawmi(void *philo);
void	free_all(t_philo *philo, int position);
void	init_forks(t_philo *philo, t_data data, int i);
void	print_forkright(t_philo *phil, long ms);
int		printf_fork_right(long ms, t_philo *phil, pthread_mutex_t *fork);

#endif