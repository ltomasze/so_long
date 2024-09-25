/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:48:04 by ltomasze          #+#    #+#             */
/*   Updated: 2024/03/24 14:34:28 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_x(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_put_x(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		ft_put_x(nb / 16, format);
		ft_put_x(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar((nb + '0'));
		else
		{
			if (format == 'x')
				ft_putchar((nb - 10 + 'a'));
			if (format == 'X')
				ft_putchar((nb - 10 + 'A'));
		}
	}
}

int	ft_putx(unsigned int nb, const char format)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		ft_put_x(nb, format);
	return (ft_len_x(nb));
}
