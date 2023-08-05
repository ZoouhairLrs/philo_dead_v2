/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:43:08 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/21 04:41:40 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*sem_arg;
	sem_t			*forks;
	long			time;
}	t_arguments;

// t_argument = t_input

typedef struct s_philo
{
	int				pid_philo;
	int				id;
	long			philo_dead;
	long			last_eat;
	int				nb_eat;
	int				nbr_eat_max;
	long			new_time;
	t_arguments		*arguments;
	sem_t			*sem;
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
void	*routine_philos(void *philo);
void	free_all(t_philo *philo, int position);
void	init_forks(t_philo *philo, t_data data, int i);
void	print_forkright(t_philo *phil, long ms);
int		printf_fork_right(long ms, t_philo *phil);
void	destroy_all(t_philo *philo, int position);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_kill_all(t_philo *philo);

#endif