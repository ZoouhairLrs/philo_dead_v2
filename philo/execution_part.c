/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:55:41 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 04:39:43 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	manage_threads(t_philo *philo, t_data *data)
{
	int	i;
	int	thread;

	i = 0;
	while (i < data->arguments->number_of_philosophers)
	{
		thread = pthread_create(&philo[i].thread, NULL,
				&routine_yawmi, &philo[i]);
		if (thread != 0)
		{
			printf ("Error...about creating threaeds!\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < data->arguments->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	init_forks(t_philo *philo, t_data data, int i)
{
	while (i < data.arguments->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].nb_eat = data.arguments->number_of_must_eat;
		data.arguments->time = get_time();
		philo[i].arguments = data.arguments;
		philo[i].new_time = get_time();
		if ((i + 1) == data.arguments->number_of_philosophers)
			philo[i].fork.left = philo[0].fork.right;
		else
			philo[i].fork.left = philo[i + 1].fork.right;
		i++;
	}
}

t_philo	*create_philo(t_data data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data.arguments->number_of_philosophers);
	if (!philo)
		return (0);
	while (i < data.arguments->number_of_philosophers)
	{
		if (pthread_mutex_init(&philo[i].mutex, NULL) != 0)
			return (printf("error inistialisation mutex..!\n"),
				destroy_all(philo, i), free(philo), NULL);
		philo[i].fork.right = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].fork.right)
			return (destroy_all(philo, i), free_all(philo, i), NULL);
		if (pthread_mutex_init(philo[i].fork.right, NULL) != 0)
			return (printf("error inistialisation mutex..!\n"),
				destroy_all(philo, i), free_all(philo, i), NULL);
		i++;
	}
	i = 0;
	init_forks(philo, data, i);
	manage_threads(philo, &data);
	return (philo);
}

int	execution_part(t_data data)
{
	t_philo	*philo;

	if (pthread_mutex_init(&data.arguments->mutex_arg, NULL) != 0)
		return (printf("error about problem inistialisation mutex..!\n"), 0);
	philo = create_philo(data);
	if (!philo)
		return (0);
	destroy_all(philo, data.arguments->number_of_philosophers);
	free_all(philo, data.arguments->number_of_philosophers);
	return (1);
}
