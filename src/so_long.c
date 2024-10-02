/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:26 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/02 17:15:04 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	dfs(int **v, int x, int y, t_game *game)
{
	int	a;
	int	b;

	a = game->height;
	b = game->width;
	if (x < 0 || x >= b || y < 0 || y >= a || game->map[y][x] == '1' || v[y][x])
		return ;
	v[y][x] = 1;
	dfs(v, x + 1, y, game);
	dfs(v, x - 1, y, game);
	dfs(v, x, y + 1, game);
	dfs(v, x, y - 1, game);
}

int	**init_visited(int width, int height)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * height);
	if (!visited)
		error_exit("Error: Memory allocation failed for visited array");
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(sizeof(int) * width);
		if (!visited[i])
			error_exit("Error: Memory allocation failed for visited row");
		j = 0;
		while (j < width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	validate_reach(t_game *game, int **v)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if ((game->map[i][j] == 'C' || game->map[i][j] == 'E') && !v[i][j])
			{
				free_visited(v, game->height);
				free_map(game);
				error_exit("Error: Not all coins and the exit are reachable");
			}
			j++;
		}
		i++;
	}
}

void	validate_paths(t_game *game)
{
	int	start_x;
	int	start_y;
	int	**visited;

	start_x = -1;
	start_y = -1;
	find_player_position(game, &start_x, &start_y);
	visited = init_visited(game->width, game->height);
	dfs(visited, start_x, start_y, game);
	validate_reach(game, visited);
	free_visited(visited, game->height);
}

int	key_press(int keycode, t_game *game)
{
	int		player_x;
	int		player_y;

	find_player_position(game, &player_x, &player_y);
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else if (keycode == 119)
		handle_move(game, player_x, player_y - 1);
	else if (keycode == 115)
		handle_move(game, player_x, player_y + 1);
	else if (keycode == 97)
		handle_move(game, player_x - 1, player_y);
	else if (keycode == 100)
		handle_move(game, player_x + 1, player_y);
	return (0);
}

/*
** keycode == 65307  Escape key
** keycode == 119    W key
** keycode == 115    S key
** keycode == 97     A key
** keycode == 100    D key
*/
/*
** x = width
** y = height
*/

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
		error_exit("Error loading wall texture");
	game->img_floor = xpm_to_img(game, "./textures/bg.xpm");
	if (!game->img_floor)
		error_exit("Error loading floor texture");
	game->img_collect = xpm_to_img(game, "./textures/coin.xpm");
	if (!game->img_collect)
		error_exit("Error loading collectible texture");
	game->img_exit = xpm_to_img(game, "./textures/exit.xpm");
	if (!game->img_exit)
		error_exit("Error loading exit texture");
	game->img_exit_open = xpm_to_img(game, "./textures/exit_open.xpm");
	if (!game->img_exit_open)
		error_exit("Error loading open exit texture");
	game->img_player = xpm_to_img(game, "./textures/player.xpm");
	if (!game->img_player)
		error_exit("Error loading player texture");
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Error initializing MLX");
	game->win = mlx_new_window(game->mlx, game->width * 100,
			game->height * 100, "so_long");
	if (!game->win)
		error_exit("Error creating window");
	game->move_count = 0;
	game->collected_items = 0;
	load_textures(game);
	render_map(game);
	mlx_key_hook(game->win, key_press, game);
	mlx_hook(game->win, 17, 0, close_window, game);
}

void	put_image_to_window(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * 100, y * 100);
}

void	exit_close_open(t_game *game, int x, int y)
{
	if (game->collected_items == game->total_items)
		put_image_to_window(game, game->img_exit_open, x, y);
	else
		put_image_to_window(game, game->img_exit, x, y);
}

void	render_map(t_game *game)
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

int	handle_exit(t_game *game)
{
	if (game->collected_items == game->total_items)
	{

		ft_printf("Congratulations! You win!\n");
		// mlx_destroy_window(game->mlx, game->win);
		// exit(0);
		close_window(game);
	}
	else
	{
		ft_printf("You need to collect all items before exiting!\n");
		return (0);
	}
	return (1);
}

void	handle_move(t_game *game, int new_x, int new_y)
{
	int		old_x;
	int		old_y;
	char	tmp;

	find_player_position(game, &old_x, &old_y);
	tmp = game->map[new_y][new_x];
	if (tmp != '1')
	{
		if (tmp == 'C')
		{
			game->collected_items++;
			game->map[new_y][new_x] = 'P';
		}
		else if (tmp == 'E' && !handle_exit(game))
			return ;
		else
			game->map[new_y][new_x] = 'P';
		game->map[old_y][old_x] = '0';
		game->move_count++;
		ft_printf("Moves: %d\n", game->move_count);
		render_map(game);
	}
}

int	set_height_width(int fd, t_game *game)
{
	char	*line;
	int		height;

	height = 0;
	game->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (process_line_width(line, game) == -1)
		{
			free(line);
			return (-1);
		}
		height++;
		free(line);
	}
	game->height = height;
	return (0);
}

int	get_map_dimensions(const char *file, t_game *game)
{
	int	fd;
	int	result;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening map file");
	result = set_height_width(fd, game);
	close(fd);
	if (result == -1 || game->height == 0 || game->width == 0)
		error_exit("Error: Empty or invalid map");
	return (0);
}

void	init_map_memory(t_game *game)
{
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		error_exit("Error allocating memory for map");
}

void	close_and_validate_map(int fd, t_game *game)
{
	close(fd);
	count_elements(game);
	check_walls(game);
	validate_paths(game);
}

int	parse_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		row;

	if (get_map_dimensions(file, game) == -1)
		return (-1);
	init_map_memory(game);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening map file");
	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[row] = ft_strtrim(line, "\n");
		if (!game->map[row])
			error_exit("Error duplicating map line");
		free(line);
		row++;
	}
	game->map[row] = NULL;
	close_and_validate_map(fd, game);
	return (0);
}

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	close_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img_collect);
	mlx_destroy_image(game->mlx, game->img_exit);
	mlx_destroy_image(game->mlx, game->img_exit_open);
	mlx_destroy_image(game->mlx, game->img_floor);
	mlx_destroy_image(game->mlx, game->img_player);
	mlx_destroy_image(game->mlx, game->img_wall);

	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);

	int	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);

	free(game->mlx);
	exit(0);
	return (0);
}
void	find_player_position(t_game *game, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("Error: Player position not found");
}

int	process_line_width(char *line, t_game *game)
{
	int	width;

	width = ft_strlen(line) - 2;
	if (line[width - 1] == '\n')
		width--;
	if (game->width == 0)
		game->width = width;
	else if (width != game->width)
		return (-1);
	return (0);
}

void	count_in_row(char *row, int width, t_game *game)
{
	int	col;

	col = 0;
	while (col < width)
	{
		if (row[col] == 'C')
			game->coins++;
		else if (row[col] == 'E')
			game->exits++;
		else if (row[col] == 'P')
			game->player++;
		col++;
	}
}

void	free_map(t_game *game)
{
	int	row;

	if (game->map)
	{
		row = 0;
		while (row < game->height)
		{
			free(game->map[row]);
			row++;
		}
		free(game->map);
	}
}

void	count_elements(t_game *game)
{
	int	row;

	game->coins = 0;
	game->exits = 0;
	game->player = 0;
	row = 0;
	while (row < game->height)
	{
		count_in_row(game->map[row], game->width, game);
		row++;
	}
	if (game->coins == 0)
	{
		free_map(game);  // Zwolnij pamięć przed wyjściem
		error_exit("Error: No coins found on the map");
	}
	if (game->exits != 1)
	{
		free_map(game);  // Zwolnij pamięć przed wyjściem
		error_exit("Error: There must be exactly one exit on the map");
	}
	if (game->player != 1)
	{
		free_map(game);  // Zwolnij pamięć przed wyjściem
		error_exit("Error: There must be exactly one player on the map");
	}
	game->total_items = game->coins;
}

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1')
		{
			free_map(game);
			error_exit("Error: Walls at the first row");
		}
		if (game->map[game->height - 1][i] != '1')
		{
			free_map(game);
			error_exit("Error: Walls at the last row");
		}
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1')
		{
			free_map(game);
			error_exit("Error: Walls at the first column, width");
		}
		if (game->map[i][game->width - 1] != '1')
		{
			free_map(game);
			error_exit("Error: Walls at the last column");
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long map.ber\n");
		return (1);
	}
	if (parse_map(argv[1], &game) == -1)
	{
		ft_printf("Error: Invalid map\n");
		return (1);
	}
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}