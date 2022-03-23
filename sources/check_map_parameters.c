/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:09:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/23 13:28:44 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void	check_map_parameters(t_game *game)
{
	int	i;

	i = 0;
	while (i <= game->map.nbr_lines)
	{
		if (check_for_invalid_map_parameters(game->map.line[i]) == TRUE)
			error_msg("Not expected map parameter");
		game->map.coins += ft_count_occurrences(game->map.line[i], COIN);
		game->map.exits += ft_count_occurrences(game->map.line[i], MAP_EXIT);
		game->map.nbr_players += ft_count_occurrences(game->map.line[i], START_POS);
		if (game->map.nbr_players == 1)
			set_start_position(&game, game->map.line[i], i);
		i++;
	}
	if (game->map.coins == 0)
		error_msg("Invalid Map. There are no collectibles!");
	else if (game->map.exit == 0)
		error_msg("Invalid Map. There are no Exit");
	else if (game->map.nbr_players != 1)
		error_msg("Invalid Map. Invalid player quantity");
}

