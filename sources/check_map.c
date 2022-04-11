/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:17:55 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/11 15:04:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_map(t_game *game)
{
	int 	i;

	i = 0;
	while(i < game->map.lines)
	{
		if ((int) strlen_line(game->map.line[i]) != game->map.columns)
			error_msg("The Map must be rectangular!");
		if ((game->map.line[i][0] != WALL)
			|| (game->map.line[i][game->map.columns - 1] != WALL))
			error_msg("The Map must be surrounded by walls! \
				A vertical wall is missing.");
		i++;
	}
	i = 0;
	while (i < game->map.columns)
	{
		if ((game->map.line[0][i] != WALL) 
			|| (game->map.line[game->map.lines - 1][i] != WALL))
			error_msg("The Map must be surrounded by walls! \
				A horizontal wall is missing.");
		i++;
	}
	check_map_parameters(game);
}
