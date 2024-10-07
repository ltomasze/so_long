/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initialize_game.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:42:04 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/07 19:49:21 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*load_xpm_image(t_game *game, char *path)
{
	int		x;
	int		y;
	void	*p;

	p = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	return (p);
}

void	load_textures(t_game *game)
{
	game->img_wall = load_xpm_image(game, "./textures/wall.xpm");
	if (!game->img_wall)
		ft_error("Error loading wall texture");
	game->img_floor = load_xpm_image(game, "./textures/bg.xpm");
	if (!game->img_floor)
		ft_error("Error loading floor texture");
	game->img_collect = load_xpm_image(game, "./textures/coin.xpm");
	if (!game->img_collect)
		ft_error("Error loading collectible texture");
	game->img_exit = load_xpm_image(game, "./textures/exit.xpm");
	if (!game->img_exit)
		ft_error("Error loading exit texture");
	game->img_exit_open = load_xpm_image(game, "./textures/exit_open.xpm");
	if (!game->img_exit_open)
		ft_error("Error loading open exit texture");
	game->img_player = load_xpm_image(game, "./textures/player.xpm");
	if (!game->img_player)
		ft_error("Error loading player texture");
}

void	draw_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * 100, y * 100);
}

void	update_exit_image(t_game *game, int x, int y)
{
	if (game->collected_items == game->total_items)
		draw_image(game, game->img_exit_open, x, y);
	else
		draw_image(game, game->img_exit, x, y);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1')
				draw_image(game, game->img_wall, x, y);
			else if (game->map[y][x] == '0')
				draw_image(game, game->img_floor, x, y);
			else if (game->map[y][x] == 'C')
				draw_image(game, game->img_collect, x, y);
			else if (game->map[y][x] == 'E')
				update_exit_image(game, x, y);
			else if (game->map[y][x] == 'P')
				draw_image(game, game->img_player, x, y);
			x++;
		}
		y++;
	}
}
