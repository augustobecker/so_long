/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:16:08 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/10 02:16:09 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

int init_map(t_map *map, char *argv)
{
	char 	*read_str;
	char	*temporary;
	int		i;

	i = 0;
	map->fd = open(argv, O_RDONLY);
	if (map->fd == -1)
		error_msg("The Map couldn't be opened. Invalid fd");
	read_str = ft_strdup(get_next_line(map->fd));
	if (!read_str)
		error_msg("Allocation failed");
	temporary = ft_strdup("");
	while (read_str)
	{
		temporary = ft_strjoin(temporary, read_str);
		read_str = get_next_line(map->fd);
	}
	map->line = ft_split(temporary, '\n');
	map->nbr_lines = ft_count_occurrences(temporary, '\n');
	map->line_len = ft_strlen(map->line[0]);
	return (1);
}
