/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:17:55 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/25 15:04:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void check_map(t_game *game)
{
	int 	i;

	i = 0;

	if (game->map.nbr_lines == game->map.line_len)
		error_msg("Square Map. The Map must be rectangular!");	
	while(i < game->map.nbr_lines)
	{
		if ((int) strlen_line(game->map.line[i]) != game->map.line_len)
			error_msg("The Map must be rectangular!");
		if ((game->map.line[i][0] != WALL)
			|| (game->map.line[i][game->map.line_len - 1] != WALL))
			error_msg("The Map must be surrounded by walls! Missing vertical wall.");
		i++;
	}
	i = 0;
	while (i < game->map.line_len)
	{
		if ((game->map.line[0][i] != WALL) 
			|| (game->map.line[game->map.nbr_lines - 1][i] != WALL))
			error_msg("The Map must be surrounded by walls! Missing horizontal wall.");
		i++;
	}
	check_map_parameters(game);
}
