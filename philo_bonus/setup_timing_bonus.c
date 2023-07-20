/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_timing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:20:54 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 06:28:53 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

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
	(void)philo;
	while (get_time() - start < t)
	{
		// pthread_mutex_lock(&philo->arguments->mutex_arg);
		// if (philo->arguments->philo_is_dead == 1)
		// {
		// 	pthread_mutex_unlock(&philo->arguments->mutex_arg);
		// 	return ;
		// }
		// pthread_mutex_unlock(&philo->arguments->mutex_arg);
		usleep(50);
	}
}

void	print_forkright(t_philo *phil, long ms)
{
	ms = get_time() - (phil->arguments->time);
	printf("%ld %d %s\n", ms, phil->id, FORK);
	sem_post(phil->arguments->sem_arg);
}

void	destroy_all(t_philo *philo, int position)
{
	int	i;

	i = 0;
	sem_close(philo->arguments->sem_arg);
	sem_close(philo->arguments->forks);
	while (i < position)
	{
		sem_close(philo[i].sem);
		i++;
	}
}
