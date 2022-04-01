/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:12:44 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/01 14:13:09 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_start_position(t_game *game, char *line, int y)
{
	int x;

	x = 0;
	while(line[x] && line[x] != PLAYER)
		x++;
	if (line[x] == '\0')
		return ;
	game->map.player.x = x;
	game->map.player.y = y;
}
