/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:17:55 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/10 02:18:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

int check_map(t_map *map)
{
	int 	i;

	i = 0;
	while(i <= map->nbr_lines)
	{
		if (ft_strlen(map->line[i]) != map->line_len)
			error_message("The Map must be rectangular!");
		if (map->line[i][0] != WALL || map->line[i][map->line_len - 1] != WALL)
			error_message("The Map must be surrounded by walls! Missing vertical wall");
		i++;
	}
	i = 0;
	while (map->line[0][i])
	{
		if (map->line[0][i] != WALL || map->line[map->nbr_lines][i] != WALL)
			error_message("The Map must be surrounded by walls! Missing horizontal wall");
		i++;
	}
	if (map->nbr_lines == map->line_len)
		error_message("The Map must be rectangular!");
	are_mapparameters_present(map);
	return (1);
}
