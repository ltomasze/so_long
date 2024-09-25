/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:10:12 by ltomasze          #+#    #+#             */
/*   Updated: 2024/03/24 14:14:53 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_uns(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_unsitoa(unsigned int nb)
{
	char	*s;
	int		len;

	len = ft_len_uns(nb);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (0);
	s[len] = '\0';
	while (nb != 0)
	{
		s[len - 1] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	return (s);
}

int	ft_putuns(unsigned int nb)
{
	int		uns_print;
	char	*s;

	uns_print = 0;
	if (nb == 0)
		uns_print = uns_print + write(1, "0", 1);
	else
	{
		s = ft_unsitoa(nb);
		uns_print = uns_print + ft_putstr(s);
		free(s);
	}
	return (uns_print);
}
