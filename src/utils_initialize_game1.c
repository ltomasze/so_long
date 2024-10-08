/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initialize_game1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:43:04 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:33 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_exit(t_game *game)
{
	if (game->collected_items == game->total_items)
	{
		ft_printf("Congratulations! You win!\n");
		destroy_window(game);
	}
	else
	{
		ft_printf("You need to collect all items before exiting!\n");
		return (0);
	}
	return (1);
}

void	player_move(t_game *game, int new_x, int new_y)
{
	int		old_x;
	int		old_y;
	char	tmp;

	locate_player(game, &old_x, &old_y);
	tmp = game->map[new_y][new_x];
	if (tmp != '1')
	{
		if (tmp == 'C')
		{
			game->collected_items++;
			game->map[new_y][new_x] = 'P';
		}
		else if (tmp == 'E' && !validate_exit(game))
			return ;
		else
			game->map[new_y][new_x] = 'P';
		game->map[old_y][old_x] = '0';
		game->move_count++;
		ft_printf("Moves: %d\n", game->move_count);
		draw_map(game);
	}
}

int	key_press(int keycode, t_game *game)
{
	int		player_x;
	int		player_y;

	locate_player(game, &player_x, &player_y);
	if (keycode == 65307)
	{
		destroy_window(game);
		exit(0);
	}
	else if (keycode == 119)
		player_move(game, player_x, player_y - 1);
	else if (keycode == 115)
		player_move(game, player_x, player_y + 1);
	else if (keycode == 97)
		player_move(game, player_x - 1, player_y);
	else if (keycode == 100)
		player_move(game, player_x + 1, player_y);
	return (0);
}

int	destroy_window(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->img_collect);
	mlx_destroy_image(game->mlx, game->img_exit);
	mlx_destroy_image(game->mlx, game->img_exit_open);
	mlx_destroy_image(game->mlx, game->img_floor);
	mlx_destroy_image(game->mlx, game->img_player);
	mlx_destroy_image(game->mlx, game->img_wall);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
	free(game->mlx);
	exit(0);
	return (0);
}
