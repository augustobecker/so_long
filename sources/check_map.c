/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:17:55 by acesar-l          #+#    #+#             */
/*   Updated: 2022/06/27 16:56:50 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_rows(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if ((int) ft_strlen_line(game->map.full[i]) != game->map.columns)
			ft_error_msg("Invalid Map. The Map must be rectangular!");
		if (game->map.full[0][i] != WALL)
			ft_error_msg("Invalid Map. \
			There's a Wall missing from the first row. \
			The Map must be surrounded by walls!.");
		if (game->map.full[game->map.rows - 1][i] != WALL)
			ft_error_msg("Invalid Map. \
			There's a Wall missing from the last row. \
			The Map must be surrounded by walls!.");
		i++;
	}
}

void	ft_check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.full[i][0] != WALL)
			ft_error_msg("Invalid Map. 
			There's a Wall missing from the first column. \
			The Map must be surrounded by walls!.");
		if (game->map.full[i][game->map.rows - 1] != WALL)
			ft_error_msg("Invalid Map. 
			There's a Wall missing from the last column. \
			The Map must be surrounded by walls!.");
		i++;
	}
}

void	ft_count_map_parameters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (ft_strchr("CEP01", game->map.full[i]))
			ft_error_msg("Invalid Map. Not expected map parameter");
		game->map.coins += line_occurrences(game->map.full[i], COINS);
		game->map.exit += line_occurrences(game->map.full[i], MAP_EXIT);
		game->map.players += line_occurrences(game->map.full[i], PLAYER);
		if (game->map.players == 1)
			ft_set_start_position(game, game->map.full[i], i);
		i++;
	}
}

void	ft_verify_map_parameters(t_game *game)
{
	if (game->map.coins == 0)
		ft_error_msg("Invalid Map. There are no Coins!");
	else if (game->map.exit == 0)
		ft_error_msg("Invalid Map. There is no Exit");
	else if (game->map.players != 1)
		ft_error_msg("Invalid Map. Invalid Player quantity. \
		It's a single player game.");
}

void	ft_check_map(t_game *game)
{
	ft_check_rows(game);
	ft_check_columns(game);
	ft_count_map_parameters(game);
	ft_verify_map_parameters(game);
}
