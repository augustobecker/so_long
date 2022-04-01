/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:36:24 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/01 19:42:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void render_map(t_game *game)
{
	int line;
	int column;

	line = 0;
	column = 0;
	while (line < game->map.nbr_lines)
	{
		while (column < game->map.line_len)
		{
			if (game->map.line[ line][column] == WALL)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
				game->wall.xpm_ptr, column * game->wall.width,  line * game->wall.height);
			if (game->map.line[ line][column] == FLOOR)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
				game->floor.xpm_ptr, column * game->floor.width,  line * game->floor.height);
			if (game->map.line[ line][column] == COINS)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
				game->coins.xpm_ptr, column * game->coins.width,  line * game->coins.height);
			if (game->map.line[ line][column] == MAP_EXIT)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
				game->exit.xpm_ptr, column * game->exit.width,  line * game->exit.height);
			if (game->map.line[line][column] == PLAYER)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
				game->player_one.xpm_ptr, column * game->player_one.width,  line * game->player_one.height);
			column++;
		}
		column = 0; 
		line++;
	}
}
