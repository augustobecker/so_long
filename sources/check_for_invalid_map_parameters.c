/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_invalid_map_parameters.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:53:54 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/01 14:27:55 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

e_bool check_for_invalid_map_parameters(char *line)
{
	int parameter;

	parameter = 0;
	while ((line[parameter]) && ft_isprint(line[parameter]) == TRUE)
	{
		if ((line[parameter] == WALL) 
			|| (line[parameter] == EMPTY_SPC)
			|| (line[parameter] == COINS) 
			|| (line[parameter] == MAP_EXIT)
			|| (line[parameter] == START_POS))
			parameter++;
		else
			return (true);
	}
	return (false);
}
