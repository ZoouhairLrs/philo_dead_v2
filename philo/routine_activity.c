/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_activity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:48 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 00:54:50 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	printf_eat(long ms, t_philo *phil)
{
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	if (phil->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		return (1);
	}
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, EAT);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	return (0);
}

int	printf_sleep(long ms, t_philo *phil)
{
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	if (phil->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		return (1);
	}
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, SLEEP);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	return (0);
}

int	printf_think(long ms, t_philo *phil)
{
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	if (phil->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		return (1);
	}
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, THINK);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	return (0);
}

int	printf_fork_left(long ms, t_philo *phil, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	if (phil->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		pthread_mutex_unlock(fork);
		return (1);
	}
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, FORK);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	return (0);
}

int	routine_activity(t_philo *phil)
{
	long	ms;

	ms = 0;
	if (printf_fork_left(ms, phil, phil->fork.left) == 1)
		return (1);
	if (printf_fork_right(ms, phil, phil->fork.right) == 1)
		return (1);
	phil->nb_eat += 1;
	pthread_mutex_lock(&phil->mutex);
	phil->new_time = get_time();
	pthread_mutex_unlock(&phil->mutex);
	if (printf_eat(ms, phil) == 1)
		return (1);
	ft_us_sleep(phil->arguments->time_to_eat, phil);
	pthread_mutex_unlock(phil->fork.left);
	pthread_mutex_unlock(phil->fork.right);
	if (phil->nb_eat >= phil->arguments->number_of_must_eat
		&& phil->arguments->number_of_must_eat != 0)
		return (1);
	if (printf_sleep(ms, phil) == 1)
		return (1);
	ft_us_sleep(phil->arguments->time_to_sleep, phil);
	if (printf_think(ms, phil) == 1)
		return (1);
	return (0);
}
