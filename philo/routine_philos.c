/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:58:28 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/26 00:45:46 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	print_dead(t_philo *philo, long ms)
{
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&philo->arguments->mutex_arg);
	philo->philo_dead = 1;
	if (philo->arguments->philo_is_dead == 1)
	{
		pthread_mutex_unlock(&philo->arguments->mutex_arg);
		return (1);
	}			
	philo->arguments->philo_is_dead = 1;
	ms = get_time() - (philo->arguments->time);
	printf("%lu %d %s\n", ms, philo->id, DIED);
	pthread_mutex_unlock(&philo->arguments->mutex_arg);
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
		pthread_mutex_lock(&philo->mutex);
		if ((get_time() - philo->new_time) >= (philo->arguments->time_to_die))
		{
			if (print_dead(philo, ms) == 1)
				break ;
		}
		else if (philo->nbr_eat_max == 1)
		{
			philo->arguments->number_phil_to_eat += 1;
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
	return (NULL);
}

void	initialization(t_philo *phil, int *i)
{
	*i = 0;
	phil->nb_eat = 0;
	phil->nbr_eat_max = 0;
	phil->philo_dead = 0;
	phil->nb_eat = 0;
	phil->arguments->philo_is_dead = 0;
}

void	*routine_philos(void *philo)
{
	int			i;
	t_philo		*phil;
	pthread_t	th_id;

	phil = (t_philo *)philo;
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	initialization (phil, &i);
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	if (phil->id % 2 == 0)
		usleep(200);
	pthread_create(&th_id, NULL, &if_stamina, phil);
	pthread_detach(th_id);
	while (1)
	{
		pthread_mutex_lock(&phil->arguments->mutex_arg);
		if (phil->arguments->philo_is_dead == 1)
			break ;
		pthread_mutex_unlock(&phil->arguments->mutex_arg);
		if (routine_activity(phil) == 1)
			return (NULL);
	}
	pthread_mutex_lock(&phil->arguments->mutex_arg);
	phil->nbr_eat_max = 1;
	pthread_mutex_unlock(&phil->arguments->mutex_arg);
	return (NULL);
}
