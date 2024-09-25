/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:59:44 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 16:42:48 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Error initializing MLX");
	game->win = mlx_new_window(game->mlx, game->width * 100,
			game->height * 100, "so_long");
	if (!game->win)
		ft_error("Error creating window");
	game->move_count = 0;
	game->collected_items = 0;
	load_textures(game);
	draw_map(game);
	mlx_key_hook(game->win, press_button, game);
	mlx_hook(game->win, 17, 0, close_window, game);
}

int	setup_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		row;

	if (get_map_size(file, game) == -1)
		return (-1);
	init_map_memory(game);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening map file");
	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[row] = ft_strtrim(line, "\n");
		if (!game->map[row])
			ft_error("Error duplicating map line");
		free(line);
		row++;
	}
	game->map[row] = NULL;
	close_and_validate_map(fd, game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file.ber>\n");
		return (1);
	}
	if (setup_map(argv[1], &game) == -1)
	{
		ft_printf("Error: Map is not valid\n");
		return (1);
	}
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}