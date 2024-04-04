/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:03:58 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/28 15:04:00 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_isint(const char *str)
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
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		if (value > 214748364 || (value == 214748364
				&& ((!neg && str[i] - '0' > 7) || (neg && str[i] - '0' > 8))))
			return (0);
		else
			value = (value * 10) + str[i++] - '0';
	}
	return (1);
}

static char	*put_int(char *str, int nb, int size, int is_neg)
{
	while (nb > 0)
	{
		*(str + size--) = nb % 10 + '0';
		nb /= 10;
	}
	if (str[1] != '\0' && size == 0 && is_neg == 1)
		*(str + size) = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		is_neg;
	char	*str;
	long	nb;
	size_t	size;

	nb = n;
	if (nb == -2147483648LL)
		return (str = ft_strdup("-2147483648"));
	else if (nb == 0)
		return (str = ft_strdup("0"));
	is_neg = 0;
	size = ft_count(nb);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (nb < 0)
	{
		is_neg = 1;
		nb = nb * -1;
	}
	str[size] = '\0';
	size--;
	put_int(str, nb, size, is_neg);
	return (str);
}
