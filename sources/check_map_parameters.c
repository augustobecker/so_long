/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:09:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/21 12:43:44 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void	check_map_parameters(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	while (i <= map->nbr_lines)
	{
		if (check_for_invalid_map_parameters(map->line[i]) == TRUE)
			error_msg("Not expected map parameter");
		game->coin += ft_count_occurrences(map->line[i], COIN);
		game->map_exit += ft_count_occurrences(map->line[i], MAP_EXIT);
		game->start_pos += ft_count_occurrences(map->line[i], START_POS);
		i++;
	}
	if (game->coin == 0)
		error_msg("There are no collectibles");
	else if (game->map_exit == 0)
		error_msg("There are no Exit");
	else if (game->start_pos != 1)
		error_msg("Invalid player quantity");
}
