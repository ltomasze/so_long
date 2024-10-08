/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_finish_map_validation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:02:21 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/08 16:31:21 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

void	validate_elements(t_game *game)
{
	if (game->coins == 0)
	{
		free_map(game);
		ft_error("Error: No coins found on the map");
	}
	if (game->exits != 1)
	{
		free_map(game);
		ft_error("Error: There must be exactly one exit on the map");
	}
	if (game->player != 1)
	{
		free_map(game);
		ft_error("Error: There must be exactly one player on the map");
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
	game->total_items = game->coins;
	validate_elements(game);
}

void	check_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1')
		{
			free_map(game);
			ft_error("Error: Walls at the first row");
		}
		if (game->map[game->height - 1][i] != '1')
		{
			free_map(game);
			ft_error("Error: Walls at the last row");
		}
		i++;
	}
}

void	check_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1')
		{
			free_map(game);
			ft_error("Error: Walls at the first column, width");
		}
		if (game->map[i][game->width - 1] != '1')
		{
			free_map(game);
			ft_error("Error: Walls at the last column");
		}
		i++;
	}
}
