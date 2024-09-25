/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_ game.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:47:15 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 16:40:33 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	position_player(t_game *game, int *player_x, int *player_y)
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

void	move(t_game *game, int new_x, int new_y)
{
	int		old_x;
	int		old_y;
	char	tmp;

	position_player(game, &old_x, &old_y);
	tmp = game->map[new_y][new_x];
	if (tmp != '1')
	{
		if (tmp == 'C')
		{
			game->collected_items++;
			game->map[new_y][new_x] = 'P';
		}
		else if (tmp == 'E' && !move_to_exit(game))
			return ;
		else
			game->map[new_y][new_x] = 'P';
		game->map[old_y][old_x] = '0';
		game->move_count++;
		ft_printf("Moves: %d\n", game->move_count);
		draw_map(game);
	}
}

int	move_to_exit(t_game *game)
{
	if (game->collected_items == game->total_items)
	{
		ft_printf("Congratulations! You win!\n");
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else
	{
		ft_printf("You need to collect all items before exiting!\n");
		return (0);
	}
	return (1);
}

int	press_button(int keycode, t_game *game)
{
	int		player_x;
	int		player_y;

	position_player(game, &player_x, &player_y);
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	else if (keycode == 119)
		move(game, player_x, player_y - 1);
	else if (keycode == 115)
		move(game, player_x, player_y + 1);
	else if (keycode == 97)
		move(game, player_x - 1, player_y);
	else if (keycode == 100)
		move(game, player_x + 1, player_y);
	return (0);
}