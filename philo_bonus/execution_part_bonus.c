/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_part_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:55:41 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 06:36:51 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo_bonus.h"

void	manage_threads(t_philo *philo, t_data *data)
{
	int	i;
	int	var;

	i = 0;
	while (i < data->arguments->number_of_philosophers)
	{
		// printf("lol1\n");
		philo[i].pid_philo = fork();
		// printf("lol2\n");
		if (philo[i].pid_philo == 0)
		{
			// printf("process is in\n");
			routine_yawmi(&philo[i]);
		}
		// printf("lol3\n");
		// thread = pthread_create(&philo[i].thread, NULL,
		// 		&routine_yawmi, &philo[i]);
		// if (thread != 0)
		// {
		// 	printf ("Error...about creating threaeds!\n");
		// 	return ;
		// }
		
		i++;
	}
	i = 0;
	while (i < data->arguments->number_of_philosophers)
	{
		waitpid(-1, &var, 0);
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
		// if ((i + 1) == data.arguments->number_of_philosophers)
		// 	philo[i].fork.left = philo[0].fork.right;
		// else
		// 	philo[i].fork.left = philo[i + 1].fork.right;
		i++;
	}
}

t_philo	*create_philo(t_data data)
{
	t_philo	*philo;
	char	*str;
	int		i;
	char	*name;
	char	*num;

	i = 0;
	str = "philo_sem";
	philo = malloc(sizeof(t_philo) * data.arguments->number_of_philosophers);
	if (!philo)
		return (0);
	while (i < data.arguments->number_of_philosophers)
	{
		num = ft_itoa(i);
		if (!num)
			return (destroy_all(philo, i), free(philo), NULL);
		name = ft_strjoin(str, num);		
		if (!name)
			return (free(num), destroy_all(philo, i), free(philo), NULL);
		sem_unlink(name);
		philo[i].sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
		if (philo[i].sem == SEM_FAILED)
			return (printf("error inistialisation mutex..!\n"),
				free(num), free(name), destroy_all(philo, i), free(philo), NULL);
		free(num);
		free(name);




		// if (pthread_mutex_init(&philo[i].mutex, NULL) != 0)
		// 	return (printf("error inistialisation mutex..!\n"),
		// 		destroy_all(philo, i), free(philo), NULL);




				
		// philo[i].fork.right = malloc(sizeof(pthread_mutex_t));
		// if (!philo[i].fork.right)
			// return (destroy_all(philo, i), free_all(philo, i), NULL);
		// if (pthread_mutex_init(philo[i].fork.right, NULL) != 0)
			// return (printf("error inistialisation mutex..!\n"),
				// destroy_all(philo, i), free_all(philo, i), NULL);
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

	philo = NULL;
	sem_unlink("new_sem");
	data.arguments->sem_arg = sem_open("new_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data.arguments->sem_arg == SEM_FAILED)
        return (printf("error inistialisation mutex..!\n"), 0);
	sem_unlink("forks");
	data.arguments->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data.arguments->number_of_philosophers);
	if (data.arguments->forks == SEM_FAILED)
        return (printf("error inistialisation mutex..!\n"), sem_close(philo->arguments->sem_arg), 0);
	// if (pthread_mutex_init(&data.arguments->sem, NULL) != 0)
	// 	return (printf("error about problem inistialisation mutex..!\n"), 0);
	philo = create_philo(data);
	if (!philo)
		return (0);
	destroy_all(philo, data.arguments->number_of_philosophers);
	free_all(philo, data.arguments->number_of_philosophers);
	return (1);
}
