/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:19:55 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 09:09:47 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "get_next_line.h"

// Struktura do przechowywania danych obrazu
typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    void    *mlx;  // Dodaj zmienną do przechowywania wskaźnika do MLX
    void    *mlx_win; // Dodaj zmienną do przechowywania wskaźnika do okna
}           t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int close_window_cross(t_data *data);
int close_window(int keycode, t_data *data);

#endif