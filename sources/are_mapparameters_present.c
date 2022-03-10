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

void are_mapparameters_present(t_map *map)
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
			break ;
		i++;
	}
	if (!coin)
		error_msg("There are no collectibles");
	if (!exit)
		error_msg("There are no Exit");
	if (!position)
		error_msg("Invalid player quantity");
}
