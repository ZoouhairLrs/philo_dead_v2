/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:44:03 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/08 19:21:12 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	init_data(t_data *data, char **argv)
{
	// initialisation part :
	data->arguments->number_of_philosophers = ft_atoi(argv[1]);
	data->arguments->time_to_die = ft_atoi(argv[2]);
	data->arguments->time_to_eat = ft_atoi(argv[3]);
	data->arguments->time_to_sleep = ft_atoi(argv[4]);
	data->arguments->time = get_time();
	// data->arguments->is_dead = 0;
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
	(void) argc;
	int	i;

	i = 0;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return(0);
	if (ft_atoi(argv[1]) == more_max_int || ft_atoi(argv[2]) == more_max_int || ft_atoi(argv[3]) == more_max_int
		|| ft_atoi(argv[4]) == more_max_int)
		return (0);
	init_data(data, argv);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_arguments arguments;

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
