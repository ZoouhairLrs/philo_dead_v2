/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_yawmi_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:58:28 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 08:28:21 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

int	print_dead(t_philo *philo, long ms)
{
	sem_post(philo->sem);
	sem_wait(philo->arguments->sem_arg);
	philo->philo_dead = 1;
	philo->arguments->philo_is_dead = 1;
	ms = get_time() - (philo->arguments->time);
	printf("%lu %d %s\n", ms, philo->id, DIED);
	return (1);
}

void	*if_stamina(void *phil)
{
	t_philo	*philo;
	long	ms;

	ms = 0;
	philo = (t_philo *)phil;
	while (philo->philo_dead != 1)
	{
		sem_wait(philo->sem);
		if ((get_time() - philo->new_time) > (philo->arguments->time_to_die))
		{
			if (print_dead(philo, ms) == 1)
				exit(0);
		}
		sem_post(philo->sem);
		usleep(100);
	}
	return (NULL);
}

void	*routine_yawmi(void *philo)
{
	int			i;
	t_philo		*phil;
	pthread_t	th_id;

	i = 0;
	phil = (t_philo *)philo;
	phil->nb_eat = 0;
	phil->nbr_eat_max = 0;
	phil->philo_dead = 0;
	phil->arguments->philo_is_dead = 0;
	phil->nb_eat = 0;
	if (phil->id % 2 == 0)
		usleep(500);
	pthread_create(&th_id, NULL, &if_stamina, phil);
	pthread_detach(th_id);
	while (1)
	{
		routine_activity(phil);
	}
	phil->nbr_eat_max = 1;
	return (NULL);
}
