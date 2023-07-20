/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 05:07:26 by zlaarous          #+#    #+#             */
/*   Updated: 2023/07/20 06:30:35 by zlaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[j] != '\0')
	{
		j++;
	}
	return (j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	i;
	size_t	j;

	if (size == 0 || size < ft_strlen(dst))
		return (size + ft_strlen(src));
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	i = 0;
	j = ld;
	while (src[i] != 0 && j + 1 < size)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (ls + ld);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!(str))
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str + (s1_len), s2, s2_len + 1);
	return (str);
}


