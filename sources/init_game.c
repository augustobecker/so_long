/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:22:27 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/11 15:22:28 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		error_msg("Couldn't find mlx pointer. Try it using a VNC.");
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
	game->map.columns * 32, game->map.lines * 32, "so_long");
	if (game->win_ptr == NULL)
		error_msg("Couldn't create the Window.");
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"../assets/sprites/wall.xpm", &game->wall.width, &game->wall.height);
	game->floor.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"../assets/sprites/floor.xpm", &game->floor.width, &game->floor.height);
	game->coins.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"../assets/sprites/coin-bag.xpm", &game->coins.width, &game->coins.height);
	game->exit.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"../assets/sprites/exit.xpm", &game->exit.width, &game->exit.height);
	game->player.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"../assets/sprites/player.xpm", &game->player.width, &game->player.height);
}
