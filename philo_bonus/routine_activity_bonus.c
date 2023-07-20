/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_activity_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:48 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 08:50:19 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

int	printf_eat(long ms, t_philo *phil)
{
	sem_wait(phil->arguments->sem_arg);
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, EAT);
	sem_post(phil->arguments->sem_arg);
	return (0);
}

int	printf_sleep(long ms, t_philo *phil)
{
	sem_wait(phil->arguments->sem_arg);
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, SLEEP);
	sem_post(phil->arguments->sem_arg);
	return (0);
}

int	printf_think(long ms, t_philo *phil)
{
	sem_wait(phil->arguments->sem_arg);
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, THINK);
	sem_post(phil->arguments->sem_arg);
	return (0);
}

int	printf_fork_left(long ms, t_philo *phil)
{
	sem_wait(phil->arguments->forks);
	sem_wait(phil->arguments->sem_arg);
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, FORK);
	sem_post(phil->arguments->sem_arg);
	return (0);
}

int	routine_activity(t_philo *phil)
{
	long	ms;

	ms = 0;
	if (printf_fork_left(ms, phil) == 1)
		return (1);
	if (printf_fork_right(ms, phil) == 1)
		return (1);
	sem_wait(phil->sem);
	phil->new_time = get_time();
	sem_post(phil->sem);
	phil->nb_eat += 1;
	if (printf_eat(ms, phil) == 1)
		return (1);
	ft_us_sleep(phil->arguments->time_to_eat, phil);
	sem_post(phil->arguments->forks);
	sem_post(phil->arguments->forks);
	if (phil->nb_eat >= phil->arguments->number_of_must_eat
		&& phil->arguments->number_of_must_eat != 0)
		exit(1);
	if (printf_sleep(ms, phil) == 1)
		return (1);
	ft_us_sleep(phil->arguments->time_to_sleep, phil);
	if (printf_think(ms, phil) == 1)
		return (1);
	return (0);
}
