/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_mapparameters_present.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:09:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/10 20:09:44 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void	are_mapparameters_present(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	game->coin = 0;
	game->map_exit = 0;
	game->start_pos = 0;
	while (i <= map->nbr_lines)
	{
		if (!are_mapparamenters(map->line[i]))
			error_msg("Not expected map parameter");
		game->coin += ft_count_occurrences(map->line[i], COIN);
		game->map_exit += ft_count_occurrences(map->line[i], MAP_EXIT);
		game->start_pos += ft_count_occurrences(map->line[i], START_POS);
		if (game->coin && game->map_exit && game->start_pos)
			break ;
		i++;
	}
	if (!game->coin)
		error_msg("There are no collectibles");
	if (!game->map_exit)
		error_msg("There are no Exit");
	if (!game->start_pos)
		error_msg("Invalid player quantity");
}
