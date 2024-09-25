/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:53:59 by ltomasze          #+#    #+#             */
/*   Updated: 2024/03/24 14:14:51 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_ptr(size_t nb)
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

void	ft_put_ptr(size_t nb)
{
	if (nb >= 16)
	{
		ft_put_ptr(nb / 16);
		ft_put_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar((nb + '0'));
		else
			ft_putchar((nb - 10 + 'a'));
	}
}

int	ft_putptr(size_t ptr)
{
	int	ptr_print;

	ptr_print = 0;
	if (ptr == 0)
		ptr_print = ptr_print + write(1, "(nil)", 5);
	else
	{
		ptr_print = ptr_print + write(1, "0x", 2);
		ft_put_ptr(ptr);
		ptr_print = ptr_print + ft_len_ptr(ptr);
	}
	return (ptr_print);
}
