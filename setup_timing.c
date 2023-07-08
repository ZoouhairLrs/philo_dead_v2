/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setuo_timing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:20:54 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/08 16:21:11 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

long	get_time(void)
{
	struct timeval	tv_time;

	gettimeofday(&tv_time, NULL);
	long current = tv_time.tv_sec * 1000 + tv_time.tv_usec / 1000;
	return (current);
}

void	ft_us_sleep(unsigned int t)
{
	long start;
	
	start = get_time();
	while (get_time() - start < t)
		usleep(50);
}
