/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:53:38 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/01 14:26:58 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include "../libraries/Libft/libft.h"

# define RED 		"\033[1;31m"
# define GREY 		"\033[0;90m"
# define RESET 		"\033[0m"

# define WALL		'1'
# define FLOOR 		'0'
# define COINS  	'C'
# define MAP_EXIT  	'E'
# define PLAYER 	'P'

enum e_bool
{
	true,
	false
};

typedef struct s_position
{
	int	x;
	int	y;
}	t_positon;

typedef struct s_image
{
	void	*xpm_ptr;
	int	width;
	int	height;
} t_image;

typedef struct s_map
{
	char		**line;
	int		nbr_lines;
	int		columns;
	int 		coins;
	int 		exit;
	int		nbr_players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int 		movements;
	t_map		map;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		exit;
	t_image		player_one;
}	t_game;

void	check_command_line_arguments(int argc, char **argv);
void	init_map(t_game *game, char *argv);
void	init_vars(t_game game);
void	check_map(t_game *game);
void	check_map_parameters(t_game *game);
e_bool	check_for_invalid_map_parameters(char *line);
void	set_start_position(t_game *game, char *line, int y);
size_t	strlen_line(char *str);
int	occurences_in_line(char *str, char c);
int	error_msg(char *message);
void	init_game(t_game *game);

#endif
