/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:44:03 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 03:58:43 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	init_data(t_data *data, char **argv)
{
	data->arguments->number_of_philosophers = ft_atoi(argv[1]);
	data->arguments->time_to_die = ft_atoi(argv[2]);
	data->arguments->time_to_eat = ft_atoi(argv[3]);
	data->arguments->time_to_sleep = ft_atoi(argv[4]);
	data->arguments->time = get_time();
	data->arguments->number_of_must_eat = 0;
	if (argv[5] != NULL)
	{
		if (ft_atoi(argv[5]) <= 0)
			return ;
		data->arguments->number_of_must_eat = ft_atoi(argv[5]);
	}
}

int	parsing_time(int argc, char **argv, t_data *data)
{
	int	i;

	(void) argc;
	i = 0;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (0);
	if (ft_atoi(argv[1]) == MAXINT || ft_atoi(argv[2]) == MAXINT
		|| ft_atoi(argv[3]) == MAXINT
		|| ft_atoi(argv[4]) == MAXINT)
		return (0);
	init_data(data, argv);
	return (1);
}

void	free_all(t_philo *philo, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		free(philo[i].fork.right);
		i++;
	}
	free(philo);
}

int	printf_fork_right(long ms, t_philo *phil, pthread_mutex_t *fork)
{
	if (phil->arguments->number_of_philosophers == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&phil->arguments->mutex_arg);
			if (phil->arguments->philo_is_dead == 1)
			{
				pthread_mutex_unlock(&phil->arguments->mutex_arg);
				pthread_mutex_unlock(fork);
				return (1);
			}			
			pthread_mutex_unlock(&phil->arguments->mutex_arg);
		}
	}
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	if (phil->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		pthread_mutex_unlock(fork);
		return (1);
	}
	print_forkright(phil, ms);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_arguments	arguments;

	data.arguments = &arguments;
	data.arguments->number_phil_to_eat = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (parsing_time(argc, argv, &data) == 0)
		return (1);
	if (execution_part(data) == 0)
		return (0);
	return (0);
}
