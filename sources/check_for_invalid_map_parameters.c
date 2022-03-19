/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_invalid_map_parameters.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:53:54 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/10 18:53:55 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool check_for_invalid_map_parameters(char *line)
{
	int parameter;

	parameter = 0;
	while (line[parameter])
	{
		if ((line[parameter] == WALL) 
			|| (line[parameter] == EMPTY_SPC)
			|| (line[parameter] == COIN) 
			|| (line[parameter] == MAP_EXIT)
			|| (line[parameter] == START_POS))
			parameter++;
		else
			return (TRUE);
	}
	return (FALSE);
}
