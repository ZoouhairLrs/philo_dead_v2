/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:02:58 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 01:08:55 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static void	space(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v'
		|| str[*i] == '\r' || str[*i] == '\f' || str[*i] == '\n')
		(*i)++;
}

static void	sign_in(char const *str, int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign *= -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	previous_result;

	sign = 1;
	result = 0;
	i = 0;
	space(str, &i);
	sign_in(str, &i, &sign);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		previous_result = result;
		result = previous_result * 10;
		if (result / 10 != previous_result)
			return (MAXINT);
		result += (str[i] - '0');
		i++;
	}
	if (result > 2147483647)
		return (MAXINT);
	return (sign * result);
}
