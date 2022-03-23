/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:12:44 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/23 13:22:09 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/Libft/libft.h"
#include "../header/so_long.h"

void set_start_position(t_game *game, char *line, int y)
{
	int x;

	x = 0;
	while(line[x] != START_POS)
		x++;
	game->map.position.x = x;
	game->map.position.y = y;
}
