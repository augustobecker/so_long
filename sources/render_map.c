/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:36:24 by acesar-l          #+#    #+#             */
/*   Updated: 2022/06/28 17:00:05 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_render_map(t_game game);
void	ft_identify_sprite(t_game *game, char parameter, int x, int y);
void	ft_render_player(t_game *game, t_image sprite, int x, int y);
void	ft_render_sprite(t_game *game, t_image sprite, int column, int line);

int	ft_render_map(t_game game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game.map.rows)
	{
		while (x < game.map.columns)
		{
			ft_identify_sprite(&game, game.map.full[y][x], y, x);
			x++;
		}
		x = 0;
		y++;
	}
	ft_print_movements(&game, game.movements);
	return (0);
}

void	ft_identify_sprite(t_game *game, char parameter, int x, int y)
{
	if (parameter == WALL)
		ft_render_sprite (game, game->wall, x, y);
	else if (parameter == FLOOR)
		ft_render_sprite (game, game->floor, x, y);
	else if (parameter == COINS)
		ft_render_sprite (game, game->coins, x, y);
	else if (parameter == MAP_EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite (game, game->open_exit, x, y);
		else
			ft_render_sprite (game, game->exit_closed, x, y);
	}
	else if (parameter == PLAYER)
		ft_render_player (game, x, y);
}

void	ft_render_player(t_game *game, int x, int y)
{
	if (game->player_sprite = FRONT)
		ft_render_sprite (game, game->player_front, x, y);
	else if (game->player_sprite = LEFT)
		ft_render_sprite (game, game->player_left, x, y);
	else if (game->player_sprite = RIGHT)
		ft_render_sprite (game, game->player_right, x, y);
	else if (game->player_sprite = BACK)]
		ft_render_sprite (game, game->player_back, x, y);
}

void	ft_render_sprite(t_game *game, t_image sprite, int column, int line)
{
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	sprite.xpm_ptr, column * sprite.x, line * sprite.y);
}
