/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:59:44 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 09:09:45 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Funkcja do rysowania piksela
void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// Funkcja do zamykania okna za pomocą "X"
int close_window_cross(t_data *data) {
    mlx_destroy_image(data->mlx, data->img); // Zniszcz obraz
    mlx_destroy_window(data->mlx, data->mlx_win); // Zniszcz okno
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0); // Zakończ program
    return (0);
}

int close_window(int keycode, t_data *data) {
    if (keycode == 65307) // ESC
    {
        close_window_cross(data); // Zakończ program, jak naciśnięto ESC
    }
    return (0);
}

int main(void) {
    t_data img; // Tworzenie zmiennej typu t_data

    img.mlx = mlx_init(); // Inicjalizuj MLX
    if (!img.mlx) // Sprawdzenie błędów
        return (1);

    img.mlx_win = mlx_new_window(img.mlx, 1920/2, 1080/2, "so_long"); // Tworzenie nowego okna
    if (!img.mlx_win) // Sprawdzenie błędów
        return (1);

    img.img = mlx_new_image(img.mlx, 1920/2, 1080/2); // Tworzenie nowego obrazu
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); // Pobieranie adresu danych obrazu

    // Przykład rysowania piksela
    my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // Rysowanie czerwonego piksela
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0); // Wyświetlanie obrazu

    // Rejestracja funkcji obsługującej zdarzenia klawiszy
    mlx_key_hook(img.mlx_win, close_window, &img);
    // Dodanie obsługi zamknięcia okna przez "X"
    mlx_hook(img.mlx_win, 17, 0, close_window_cross, &img);
    mlx_loop(img.mlx); // Rozpoczęcie pętli MLX
    return (0);
}