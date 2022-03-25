/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:19:36 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/25 12:21:06 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void init_vars(t_game *game)
{
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.nbr_players = 0;
	game->movements = 0;
}
