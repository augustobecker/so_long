/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:53:38 by acesar-l          #+#    #+#             */
/*   Updated: 2022/06/21 01:06:58 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../libraries/Libft/libft.h"

# define GREEN			"\033[0;32m"
# define RED 			"\033[1;31m"
# define GREY 			"\033[0;90m"
# define RESET 			"\033[0m"

# define WALL			'1'
# define FLOOR 			'0'
# define COINS  		'C'
# define PLAYER			'P'
# define MAP_EXIT 		'E'
# define TOXIC			'T'

# define WALL_XPM		"../assets/sprites/wall.xpm"
# define FLOOR_XPM		"../assets/sprites/floor.xpm"
# define COINS_XPM		"../assets/sprites/coin-bag.xpm"
# define PLAYER_FRONT_XPM	"../assets/sprites/player/front.xpm"
# define PLAYER_LEFT_XPM	"../assets/sprites/player/left.xpm"
# define PLAYER_RIGHT_XPM	"../assets/sprites/player/right.xpm"
# define PLAYER_BACK_XPM	"../assets/sprites/player/back.xpm"
# define OPEN_EXIT_XPM		"../assets/sprites/open-exit.xpm"
# define EXIT_CLOSED_XPM	"../assets/sprites/exit-closed.xpm"
# define TOXIC_XPM		"../assets/sprites/toxic-river.xpm"

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
	int	x;
	int	y;
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
	t_image		open_exit;
	t_image		exit_closed;
	t_image		player_right;
	t_image		player_left;
	t_image		player_back;
	t_image		player_front;
	t_image		toxic;
}	t_game;

void	ft_check_command_line_arguments(int argc, char **argv);
void	ft_init_vars(t_game *game);
void	ft_init_map(t_game *game, char *argv);
void	ft_check_map(t_game *game);
void	ft_check_map_parameters(t_game *game);
t_bool	ft_check_for_invalid_map_parameters(char *line);
void	ft_init_mlx(t_game *game);
void	ft_init_sprites(t_game *game);

size_t	ft_strlen_line(char *str);
int	ft_count_line_occurrences(char *str, char c);
void	ft_set_start_position(t_game *game, char *line, int y);

#endif
