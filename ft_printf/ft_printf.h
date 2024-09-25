/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:37 by ltomasze          #+#    #+#             */
/*   Updated: 2024/03/24 14:28:09 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putarg(va_list args, const char format);
char	*ft_uint_in_str(char *s, unsigned int number, int len);
int		ft_len_int(int n);
char	*ft_itoa(int n);
int		ft_putnbr(int n);
int		ft_len_ptr(size_t nb);
void	ft_put_ptr(size_t nb);
int		ft_putptr(size_t ptr);
int		ft_len_uns(unsigned int nb);
char	*ft_unsitoa(unsigned int nb);
int		ft_putuns(unsigned int nb);
int		ft_len_x(unsigned int nb);
void	ft_put_x(unsigned int nb, const char format);
int		ft_putx(unsigned int nb, const char format);

#endif