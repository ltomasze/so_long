/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:59:44 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/24 12:15:51 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init(); // Inicjalizuj MLX
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 800, 600, "So Long!"); // Twórz nowe okno
    if (!win)
        return (1);
    mlx_loop(mlx); // Rozpocznij pętlę MLX
    return (0);
}