/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_timing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:20:54 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 00:55:02 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

long	get_time(void)
{
	struct timeval	tv_time;
	long			current;

	gettimeofday(&tv_time, NULL);
	current = tv_time.tv_sec * 1000 + tv_time.tv_usec / 1000;
	return (current);
}

void	ft_us_sleep(unsigned int t, t_philo *philo)
{
	long	start;

	start = get_time();
	while (get_time() - start < t)
	{
		pthread_mutex_lock(&philo->arguments->mutex_arg);
		if (philo->arguments->philo_is_dead == 1)
		{
			pthread_mutex_unlock(&philo->arguments->mutex_arg);
			return ;
		}
		pthread_mutex_unlock(&philo->arguments->mutex_arg);
		usleep(50);
	}
}

void	print_forkright(t_philo *phil, long ms)
{
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, FORK);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
}
