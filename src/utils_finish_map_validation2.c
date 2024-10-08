/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_finish_map_validation2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:25:10 by ltomasze          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:22 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
