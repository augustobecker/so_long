/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:09:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/02 06:28:44 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_parameters(t_game *game)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (i <= game->map.nbr_lines)
	{
		if (check_for_invalid_map_parameters(game->map.line[i]) == true)
			error_msg("Not expected map parameter");
		game->map.coins += occurences_in_line(game->map.line[i], COINS);
		game->map.exits += occurences_in_line(game->map.line[i], MAP_EXIT);
		game->map.nbr_players += occurences_in_line(game->map.line[i], PLAYER);
		if (game->map.nbr_players == 1 && player == 0)
		{
			set_start_position(&game, game->map.line[i], i);
			player++;
		}
		i++;
	}
	if (game->map.coins == 0)
		error_msg("Invalid Map. There are no collectibles!");
	else if (game->map.exit == 0)
		error_msg("Invalid Map. There is no Exit!");
	else if (game->map.nbr_players != 1)
		error_msg("Invalid Map. Invalid player quantity!");
}

