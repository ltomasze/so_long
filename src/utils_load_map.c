/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_load_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:52:26 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:01 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_line_width(char *line, t_game *game)
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

int	set_height_width(int fd, t_game *game)
{
	char	*line;
	int		height;
	int		res;

	res = 0;
	height = 0;
	game->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_line_width(line, game) == -1)
			res = -1;
		height++;
		free(line);
	}
	if (res == -1)
		return (-1);
	game->height = height;
	return (0);
}

void	allocate_map_memory(t_game *game)
{
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		ft_error("Error allocating memory for map");
}

void	finish_map_validation(int fd, t_game *game)
{
	close(fd);
	count_elements(game);
	check_horizontal_walls(game);
	check_vertical_walls(game);
	validate_paths(game);
}

int	load_map_size(const char *file, t_game *game)
{
	int	fd;
	int	result;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening map file");
	result = set_height_width(fd, game);
	close(fd);
	if (result == -1 || game->height == 0 || game->width == 0)
		ft_error("Error: Empty or invalid map");
	return (0);
}
