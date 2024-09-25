/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:19:55 by ltomasze          #+#    #+#             */
/*   Updated: 2024/09/25 17:02:00 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "get_next_line.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	char	**map;
	int		move_count;
	int		total_items;
	int		collected_items;
	void	*img_wall;
	void	*img_floor;
	void	*img_collect;
	void	*img_exit;
	void	*img_exit_open;
	void	*img_player;
	int		coins;
	int		exits;
	int		player;
}	t_game;

void	ft_error(const char *msg);
void	position_player(t_game *game, int *player_x, int *player_y);
void	init_game(t_game *game);
void	move(t_game *game, int new_x, int new_y);
void	*xpm_to_img(t_game *game, char *path);
void	load_textures(t_game *game);
void	close_and_validate_map(int fd, t_game *game);
void	put_image_to_window(t_game *game, void *img, int x, int y);
void	draw_map(t_game *game);
int	close_window(t_game *game);
int	press_button(int keycode, t_game *game);
int	move_to_exit(t_game *game);
int	setup_map(const char *file, t_game *game);

#endif