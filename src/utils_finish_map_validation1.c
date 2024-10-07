/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_finish_map_validation1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:14:24 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/07 20:22:43 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	locate_player(t_game *game, int *player_x, int *player_y)
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
	ft_error("Error: Player position not found");
}

int	**init_visited(int width, int height)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * height);
	if (!visited)
		ft_error("Error: Memory allocation failed for visited array");
	i = 0;
	while (i < height)
	{
		visited[i] = (int *)malloc(sizeof(int) * width);
		if (!visited[i])
			ft_error("Error: Memory allocation failed for visited row");
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

void	DepthFirstSearch(int **v, int x, int y, t_game *game)
{
	int	a;
	int	b;

	a = game->height;
	b = game->width;
	if (x < 0 || x >= b || y < 0 || y >= a || game->map[y][x] == '1' || v[y][x])
		return ;
	v[y][x] = 1;
	DepthFirstSearch(v, x + 1, y, game);
	DepthFirstSearch(v, x - 1, y, game);
	DepthFirstSearch(v, x, y + 1, game);
	DepthFirstSearch(v, x, y - 1, game);
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
				ft_error("Error: Not all coins and the exit are reachable");
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
	locate_player(game, &start_x, &start_y);
	visited = init_visited(game->width, game->height);
	DepthFirstSearch(visited, start_x, start_y, game);
	validate_reach(game, visited);
	free_visited(visited, game->height);
}