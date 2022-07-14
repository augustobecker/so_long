/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:02:23 by acesar-l          #+#    #+#             */
/*   Updated: 2022/07/14 04:06:18 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_check_command_line_arguments(int argc, char **argv, t_game *game);
void	ft_init_map(t_game *game, char *argv);
t_bool	ft_check_for_empty_line(char *map);

void	ft_check_command_line_arguments(int argc, char **argv, t_game *game)
{
	int	map_parameter_len;

	game->map_alloc = false;
	if (argc > 2)
		ft_error_msg("Too many arguments (It should be only two).", game);
	if (argc < 2)
		ft_error_msg("The Map file is missing.", game);
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		ft_error_msg("Map file extention is wrong (It should be .ber).", game);
}

void	ft_init_map(t_game *game, char *argv)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("The Map couldn't be opened. Does the Map exist?", game);
	map_temp = ft_strdup("");
	game->map.rows = 0;
	while (true)
	{
		line_temp = get_next_line(map_fd);
		if (line_temp == NULL)
			break ;
		map_temp = ft_strappend(&map_temp, line_temp);
		free(line_temp);
		game->map.rows++;
	}
	game->map_alloc = true;
	close(map_fd);
	if (ft_check_for_empty_line(map_temp) == true)
		ft_error_msg("Invalid map. The map have an empty line.", game);
	game->map.full = ft_split(map_temp, '\n');
	free(map_temp);
}

t_bool	ft_check_for_empty_line(char *map)
{
	int	i;

	i = 1;
	if (map[0] == '\n')
	{
		free(map);
		return (true);
	}
	else if (map[ft_strlen(map)] - 1 == '\n')
	{
		free (map);
		return (true);
	}
	while (map[i])
	{
		if (map[i - 1] == '\n' && map[i] == '\n')
		{
			free(map);
			return (true);
		}
		i++;
	}
	return (false);
}
