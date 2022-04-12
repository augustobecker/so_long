/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:16:12 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/12 01:44:17 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "Libft/libft.h"

# define GREEN	"\033[0;32m"
# define RED 	"\033[1;31m"
# define GREY 	"\033[0;90m"
# define RESET 	"\033[0m"

# define WALL		'1'
# define COINS  	'C'
# define MAP_EXIT  	'E'
# define PLAYER		'P'
# define EMPTY_SPC  '0'

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

# define KEY_W_u	87
# define KEY_A_u	65
# define KEY_S_u	83
# define KEY_D_u	68

# define KEY_UP  	65362
# define KEY_LEFT  	65361
# define KEY_RIGHT 	65363
# define KEY_DOWN  	65364

# define KEY_Q		113
# define KEY_ESC  	65307

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
	int		width;
	int		height;
} t_image;

typedef struct s_map
{
	char		**line;
	int			lines;
	int			columns;
	int 		coins;
	int 		exit;
	int			players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int 		movements;
	t_map		map;
	t_image		wall;
	t_image		player;
	t_image		floor;
	t_image		coins;
	t_image		exit;
}	t_game;


static int handle_no_event(void *game)
{
	return (0);
}

int error_msg(char *message)
{
	ft_printf(RED"Error\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}

// 2nd 'n 3rd parameters - ponto futuro do player
// game->map.line[line][column] - posição futura

void render_player_move(t_game *game, int line, int column)
{
	game->map.line[game->map.player.y][game->map.player.x] = EMPTY_SPC;
	game->map.line[line][column] = PLAYER;
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	game->floor.xpm_ptr, game->map.player.x * game->floor.width, \
	 game->map.player.y * game->floor.height);
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	game->player.xpm_ptr, column * game->player.width, \
	line * game->player.height);
	game->map.player.x = column;
	game->map.player.y = line;
	game->movements++;
	ft_printf("Movements: %d\n", game->movements);
}

void player_move(t_game *game, int line, int column)
{
	if (game->map.line[line][column] == EMPTY_SPC)
	{
		render_player_move(game, line, column);
		return ;
	}
	if (game->map.line[line][column] == COINS)
	{
		render_player_move(game, line, column);
		game->map.coins--;
		return ;
	}
	if (game->map.line[line][column] == MAP_EXIT && game->map.coins == 0)
	{
		ft_printf(GREEN"YOU WON\n"RESET);
		exit (EXIT_FAILURE);
	}
}

int handle_input(int keysym, t_game *game)
{
	int	column;
	int	line;
	
	column = game->map.player.x;
	line = game->map.player.y;
	if (keysym == KEY_Q || keysym == KEY_ESC)
	{
		//free_game(t_game *game);
		error_msg("Escape key was pressed");
		return (0);
	}
	if (keysym == KEY_UP || keysym == KEY_W)
		player_move(game, --line, column);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		player_move(game, line, --column);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		player_move(game, line, ++column);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		player_move(game, ++line, column);
	return (0);
}

void init_vars(t_game *game)
{
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.players = 0;
	game->movements = 0;
}

size_t strlen_line(char *str)
{
	size_t	length;

	length = 0;
	while (str[length] && ft_isprint(str[length]))
		length++;
	return (length);
}

void check_command_line_arguments(int argc, char **argv)
{
	int map_parameter_len;

	if (argc > 10)
		error_msg("Too many arguments (It should be only two).");
	if (argc < 2)
		error_msg("The Map file is missing");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		error_msg("Map file extention is wrong (It should be .ber).");
}

t_bool check_for_invalid_map_parameters(char *line)
{
	int parameter;

	parameter = 0;
	while ((line[parameter]) && ft_isprint(line[parameter]) == true)
	{
		if ((line[parameter] == WALL) 
			|| (line[parameter] == EMPTY_SPC)
			|| (line[parameter] == COINS) 
			|| (line[parameter] == MAP_EXIT)
			|| (line[parameter] == PLAYER))
			parameter++;
		else
			return (true);
	}
	return (false);
}

void init_map(t_game *game, char *argv)
{
	char 	*read_str;
	char	*temporary;
	int		map_fd;
	int		i;

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
	close(map_fd);
	game->map.line = ft_split(temporary, '\n');
	game->map.lines = ft_count_occurrences(temporary, '\n');
	game->map.lines++;
	game->map.columns = strlen_line(game->map.line[0]);
}


//CHANGE ON GITHUB
void set_start_position(t_game *game, char *line, int y)
{
	int x;

	x = 0;
	while(line[x] && line[x] != PLAYER)
		x++;
	if (line[x] == '\0')
		return ;
	game->map.player.x = x;
	game->map.player.y = y;
}
// this function

int	count_occurrences(char *str, char c)
{
	int	occurrences;
	int	i;

	i = 0;
	occurrences = 0;
	while (str[i] && ft_isprint(str[i]))
	{
		if (str[i] == c)
			occurrences++;
		i++;
	}
	return (occurrences);
}


void	check_map_parameters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.lines)
	{
		if (check_for_invalid_map_parameters(game->map.line[i]) == 1)
			error_msg("Not expected map parameter");
		game->map.coins += count_occurrences(game->map.line[i], COINS);
		game->map.exit += count_occurrences(game->map.line[i], MAP_EXIT);
		game->map.players += count_occurrences(game->map.line[i], PLAYER);
		if (game->map.players == 1)
			set_start_position(game, game->map.line[i], i);
		i++;
	}
	if (game->map.coins == 0)
		error_msg("Invalid Map. There are no collectibles!");
	else if (game->map.exit == 0)
		error_msg("Invalid Map. There is no Exit");
	else if (game->map.players != 1)
		error_msg("Invalid Map. Invalid player quantity.");
}

void check_map(t_game *game)
{
	int 	i;

	i = 0;
	while(i < game->map.lines)
	{
		if ((int) strlen_line(game->map.line[i]) != game->map.columns)
			error_msg("The Map must be rectangular!");
		if ((game->map.line[i][0] != WALL)
			|| (game->map.line[i][game->map.columns - 1] != WALL))
			error_msg("The Map must be surrounded by walls! \
				A vertical wall is missing.");
		i++;
	}
	i = 0;
	while (i < game->map.columns)
	{
		if ((game->map.line[0][i] != WALL) 
			|| (game->map.line[game->map.lines - 1][i] != WALL))
			error_msg("The Map must be surrounded by walls! \
				A horizontal wall is missing.");
		i++;
	}
	check_map_parameters(game);
}

void print_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < game->map.lines)
	{
		while (i < game->map.columns)
		{
			if (game->map.line[j][i] == WALL)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->wall.xpm_ptr, i * game->wall.width, j * game->wall.height);
			if (game->map.line[j][i] == EMPTY_SPC)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->floor.xpm_ptr, i * game->floor.width, j * game->floor.height);
			if (game->map.line[j][i] == COINS)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->coins.xpm_ptr, i * game->coins.width, j * game->coins.height);
			if (game->map.line[j][i] == MAP_EXIT)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->exit.xpm_ptr, i * game->exit.width, j * game->exit.height);
			if (game->map.line[j][i] == PLAYER)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->player.xpm_ptr, i * game->player.width, j * game->player.height);
			i++;
		}
		i = 0; 
		j++;
	}
}

void print_player(t_game *game, int pos_x, int pos_y)
{
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->floor.xpm_ptr, pos_x * game->floor.width, pos_y * game->floor.height);
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->player.xpm_ptr, (pos_x + 1) * game->player.width, pos_y * game->player.height);
}


void init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		error_msg("Couldn't find mlx pointer. Try it using a VNC.");
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
	game->map.columns * 32, game->map.lines * 32, "so_long");
	if (game->win_ptr == NULL)
		error_msg("Couldn't create the Window.");
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"folder/assets/sprites/wall.xpm", &game->wall.width, &game->wall.height);
	game->floor.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"folder/assets/sprites/floor.xpm", &game->floor.width, &game->floor.height);
	game->coins.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"folder/assets/sprites/coin-bag.xpm", &game->coins.width, &game->coins.height);
	game->exit.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"folder/assets/sprites/exit.xpm", &game->exit.width, &game->exit.height);
	game->player.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"folder/assets/sprites/player.xpm", &game->player.width, &game->player.height);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int i;
	
	check_command_line_arguments(argc, argv);
	init_vars(&game);
	init_map(&game, argv[1]);
	check_map(&game);
	i = 0;
	while (i <= game.map.lines)
		ft_putendl_fd(game.map.line[i++], 1);
	init_game(&game);
	print_map(&game);
	mlx_hook(game.win_ptr, 3, 1L << 1, handle_input, &game);
	mlx_loop_hook(game.mlx_ptr, &handle_no_event, &game);
	mlx_loop(game.mlx_ptr);
	mlx_destroy_display(game.mlx_ptr);
	free(game.mlx_ptr);
}
