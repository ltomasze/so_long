/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:54:04 by ltomasze          #+#    #+#             */
/*   Updated: 2024/03/24 14:14:50 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uint_in_str(char *s, unsigned int number, int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

int	ft_len_int(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				len;
	unsigned int	number;
	int				sign;

	sign = 1;
	len = ft_len_int(n);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign = sign * -1;
		number = n * -1;
		s[0] = '-';
	}
	else
		number = n;
	s = ft_uint_in_str(s, number, len);
	return (s);
}

int	ft_putnbr(int n)
{
	int		len;
	char	*num;

	num = ft_itoa(n);
	len = ft_putstr(num);
	free(num);
	return (len);
}
