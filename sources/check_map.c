/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:17:55 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/21 16:51:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void check_map(t_game *game)
{
	int 	i;

	i = 0;
	if (game->map_nbr_lines == game->map_line_len)
		error_msg("Square Map. The Map must be rectangular!");	
	while(i <= map->nbr_lines)
	{
		if (ft_strlen(game->map[i]) != game->map_line_len)
			error_msg("The Map must be rectangular!");
		if (game->map[i][0] != WALL || game->map[i][game->map_line_len - 1] != WALL)
			error_msg("The Map must be surrounded by walls! Missing vertical wall");
		i++;
	}
	i = 0;
	while (i < game->map_line_len)
	{
		if (game->map[0][i] != WALL || game->line[game->map_nbr_lines][i] != WALL)
			error_msg("The Map must be surrounded by walls! Missing horizontal wall");
		i++;
	}
	check_map_parameters(game);
}
