/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:16:08 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/22 11:56:09 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void init_map(t_game *game, char *argv)
{
	char 	*read_str;
	char	*temporary;
	int	map_fd;
	int	i;

	i = 0;
	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		error_msg("The Map couldn't be opened. Invalid fd");
	read_str = ft_strdup(get_next_line(map_fd));
	if (!read_str)
		error_msg("Allocation failed");
	temporary = ft_strdup("");
	while (read_str)
	{
		temporary = ft_strjoin(temporary, read_str);
		read_str = get_next_line(map_fd);
	}
	game->map.line = ft_split(temporary, '\n');
	game->map.nbr_lines = ft_count_occurrences(temporary, '\n');
	game->map.line_len = ft_strlen(game->map[0]);
}
