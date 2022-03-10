/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_mapparameters_present.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:09:43 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/10 18:09:44 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int are_mapparameters_present(t_map *map)
{
	int coin;
	int exit;
	int position;
	int i;

	i = 0;
	coin = 0;
	exit = 0;
	position = 0;
	while (i <= map->nbr_lines)
	{
		coin += ft_count_occurrences(map->line[i], COIN);
		exit += ft_count_occurrences(map->line[i], MAP_EXIT);
		position += ft_count_occurrences(map->line[i], START_POS);
		if (coin && exit && position)
			return (1);
		i++;
	}
	if (!coin)
		return (error_msg("There are no collectibles"));
	if (!exit)
		return (error_msg("There are no Exit"));
	if (!position)
		return (error_msg("Invalid player quantity"));
	return (1);
}
