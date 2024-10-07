/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:19:55 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/07 19:32:17 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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

void	free_map(t_game *game);

/* Game */
void	initialize_game(t_game *game);
void	*load_xpm_image(t_game *game, char *path);
void	load_textures(t_game *game);
int		key_press(int keycode, t_game *game);

/* Graphics */
void	draw_image(t_game *game, void *img, int x, int y);
void	draw_map(t_game *game);
void	player_move(t_game *game, int new_x, int new_y);
int		validate_exit(t_game *game);
void	update_exit_image(t_game *game, int x, int y);

/* Map */
int		set_height_width(int fd, t_game *game);
int		load_map_size(const char *file, t_game *game);
void	allocate_map_memory(t_game *game);
void	finish_map_validation(int fd, t_game *game);
int		load_map(const char *file, t_game *game);

/* Utils */
void	ft_error(const char *msg);
int		destroy_window(t_game *game);
void	locate_player(t_game *game, int *player_x, int *player_y);
int		check_line_width(char *line, t_game *game);

/* Validation */
void	count_in_row(char *row, int width, t_game *game);
void	count_elements(t_game *game);
void	validate_elements(t_game *game);
void	check_horizontal_walls(t_game *game);
void	check_vertical_walls(t_game *game);

/* DFS Depth-First Search*/
void	dfs(int **v, int x, int y, t_game *game);
int		**init_visited(int width, int height);
void	free_visited(int **visited, int height);
void	validate_reach(t_game *game, int **v);
void	validate_paths(t_game *game);
#endif
