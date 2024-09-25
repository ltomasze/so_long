/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:34:49 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 17:01:03 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*xpm_to_img(t_game *game, char *path)
{
	int		x;
	int		y;
	void	*p;

	p = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	return (p);
}

void	load_textures(t_game *game)
{
	game->img_wall = xpm_to_img(game, "./textures/wall.xpm");
	if (!game->img_wall)
		ft_error("Error loading wall texture");
	game->img_floor = xpm_to_img(game, "./textures/bg.xpm");
	if (!game->img_floor)
		ft_error("Error loading floor texture");
	game->img_collect = xpm_to_img(game, "./textures/coin.xpm");
	if (!game->img_collect)
		ft_error("Error loading collectible texture");
	game->img_exit = xpm_to_img(game, "./textures/exit.xpm");
	if (!game->img_exit)
		ft_error("Error loading exit texture");
	game->img_exit_open = xpm_to_img(game, "./textures/exit_open.xpm");
	if (!game->img_exit_open)
		ft_error("Error loading open exit texture");
	game->img_player = xpm_to_img(game, "./textures/player.xpm");
	if (!game->img_player)
		ft_error("Error loading player texture");
}

void	close_and_validate_map(int fd, t_game *game)
{
	close(fd);
	count_elements(game);
	check_walls(game);
	validate_paths(game);
}
void	put_image_to_window(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * 100, y * 100);
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
				put_image_to_window(game, game->img_wall, x, y);
			else if (game->map[y][x] == '0')
				put_image_to_window(game, game->img_floor, x, y);
			else if (game->map[y][x] == 'C')
				put_image_to_window(game, game->img_collect, x, y);
			else if (game->map[y][x] == 'E')
				exit_close_open(game, x, y);
			else if (game->map[y][x] == 'P')
				put_image_to_window(game, game->img_player, x, y);
			x++;
		}
		y++;
	}
}