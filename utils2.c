/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:43:15 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/29 15:43:16 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		if (value > MAX_LONG || (value == MAX_LONG
				&& ((!neg && str[i] - '0' > 7) || (neg && str[i] - '0' > 8))))
			return (-1 * !neg);
		else
			value = (value * 10) + str[i++] - '0';
	}
	if (neg)
		value = -value;
	return (value);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	while (*s1)
		ptr[i++] = *s1++;
	ptr[i] = '\0';
	return (ptr);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
