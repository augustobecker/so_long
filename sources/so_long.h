/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:53:38 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/04 11:36:58 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "../libraries/Libft/libft.h"

# define GREEN			"\033[0;32m"
# define RED 			"\033[1;31m"
# define GREY 			"\033[0;90m"
# define RESET 			"\033[0m"

# define WALL			'1'
# define COINS  		'C'
# define MAP_EXIT 	 	'E'
# define PLAYER			'P'
# define FLOOR 			'0'
# define TOXIC			'T'
# define SPIKES			'S'

# define WALL_XPM		"assets/folder/assets/sprites/wall.xpm"
# define COINS_XPM		"assets/folder/assets/sprites/coin-bag.xpm"
# define OPEN_EXIT_XPM		"assets/folder/assets/sprites/open-exit.xpm"
# define EXIT_CLOSED_XPM	"assets/folder/assets/sprites/exit-closed.xpm"
# define PLAYER_FRONT_XPM	"assets/folder/assets/sprites/player/front.xpm"
# define PLAYER_LEFT_XPM	"assets/folder/assets/sprites/player/left.xpm"
# define PLAYER_RIGHT_XPM	"assets/folder/assets/sprites/player/right.xpm"
# define PLAYER_BACK_XPM	"assets/folder/assets/sprites/player/back.xpm"
# define FLOOR_XPM		"assets/folder/assets/sprites/floor.xpm"
# define TOXIC_XPM		"assets/folder/assets/sprites/toxic-river.xpm"
# define SPIKES_XPM		"assets/folder/assets/sprites/spikes.xpm"

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100

# define KEY_UP  		65362
# define KEY_LEFT  		65361
# define KEY_RIGHT 		65363
# define KEY_DOWN  		65364

# define KEY_Q			113
# define KEY_ESC  		65307

#define FRONT			1
#define LEFT			2
#define RIGHT			3
#define BACK			4

typedef enum e_bool
{
	false,
	true
}	t_bool;

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
	int		lines;
	int		columns;
	int 		coins;
	int 		exit;
	int		players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int 		movements;
	int		player_sprite;
	t_map		map;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		exit_open;
	t_image		exit_closed;
	t_image		player_right;
	t_image		player_left;
	t_image		player_back;
	t_image		player_front;
	t_image		toxic;
	t_image		spikes;
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
