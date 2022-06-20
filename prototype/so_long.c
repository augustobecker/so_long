/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:16:12 by acesar-l          #+#    #+#             */
/*   Updated: 2022/06/20 15:08:40 by acesar-l         ###   ########.fr       */
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
#include "../assets/folder/libraries/Libft/libft.h"

# define GREEN				"\033[0;32m"
# define RED 				"\033[1;31m"
# define GREY 				"\033[0;90m"
# define RESET 				"\033[0m"

# define WALL				'1'
# define FLOOR 				'0'
# define COINS  			'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'
# define TOXIC				'T'
# define SPIKES				'S'

# define WALL_XPM			"assets/folder/assets/sprites/wall.xpm"
# define FLOOR_XPM			"assets/folder/assets/sprites/floor.xpm"
# define COINS_XPM			"assets/folder/assets/sprites/coin-bag.xpm"
# define PLAYER_FRONT_XPM	"assets/folder/assets/sprites/player/front.xpm"
# define PLAYER_LEFT_XPM	"assets/folder/assets/sprites/player/left.xpm"
# define PLAYER_RIGHT_XPM	"assets/folder/assets/sprites/player/right.xpm"
# define PLAYER_BACK_XPM	"assets/folder/assets/sprites/player/back.xpm"
# define OPEN_EXIT_XPM		"assets/folder/assets/sprites/open-exit.xpm"
# define EXIT_CLOSED_XPM	"assets/folder/assets/sprites/exit-closed.xpm"
# define TOXIC_XPM			"assets/folder/assets/sprites/toxic-river.xpm"
# define SPIKES_XPM			"assets/folder/assets/sprites/spikes.xpm"

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

# define KEY_UP  	65362
# define KEY_LEFT  	65361
# define KEY_RIGHT 	65363
# define KEY_DOWN  	65364

# define KEY_Q		113
# define KEY_ESC  	65307

#define FRONT		1
#define LEFT		2
#define RIGHT		3
#define BACK		4

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
	int		x;
	int		y;
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
	int			player_sprite;
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
	t_image		spikes;
}	t_game;


static int ft_handle_no_event(void *game)
{
	return (0);
}

int ft_error_msg(char *message)
{
	ft_printf(RED"Error\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}

int	ft_count_occurrences(char *str, char c)
{
	int	occurrences;
	int	i;

	i = 0;
	occurrences = 0;
	while (str[i])
	{
		if (str[i] == c)
			occurrences++;
		i++;
	}
	return (occurrences);
}

void ft_render_player_move(t_game *game, int line, int column)
{
	char *num;
	int i;
	
	i = 0;
	game->map.line[game->map.player.y][game->map.player.x] = FLOOR;
	game->map.line[line][column] = PLAYER;
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	game->floor.xpm_ptr, game->map.player.x * game->floor.y, \
	 game->map.player.y * game->floor.x);
	if (game->player_sprite == FRONT)
	{
		mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
		game->player_back.xpm_ptr, column * game->player_back.y, \
		line * game->player_back.x);
	}
	if (game->player_sprite == LEFT)
	{
		mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
		game->player_left.xpm_ptr, column * game->player_left.y, \
		line * game->player_left.x);
	}
	if (game->player_sprite == RIGHT)
	{
		mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
		game->player_right.xpm_ptr, column * game->player_right.y, \
		line * game->player_right.x);
	}
	 if (game->player_sprite == BACK)
	{
		mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
		game->player_front.xpm_ptr, column * game->player_front.y, \
		line * game->player_front.x);
	}
	game->map.player.x = column;
	game->map.player.y = line;
	game->movements++;
	num = ft_itoa(game->movements);
	while (i < game->map.columns)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->wall.xpm_ptr, i++ * game->wall.y, 0 * game->wall.x);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 30, 22, 99999 , ft_strjoin("Movements : ", num));
	free(num);
}

void ft_render_open_exit(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < game->map.lines)
	{
		while (i < game->map.columns)
		{
			if (game->map.line[j][i] == MAP_EXIT)
				mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, game->open_exit.xpm_ptr, i * game->open_exit.y, j * game->open_exit.x);
			i++;
		}
		i = 0; 
		j++;
	}
}

void ft_player_move(t_game *game, int line, int column)
{
	if (game->map.line[line][column] == FLOOR)
	{
		ft_render_player_move(game, line, column);
		return ;
	}
	if (game->map.line[line][column] == COINS)
	{
		ft_render_player_move(game, line, column);
		game->map.coins--;
		if (game->map.coins == 0)
			ft_render_open_exit(game);
	}
	if (game->map.line[line][column] == TOXIC || game->map.line[line][column] == SPIKES)
	{
		ft_error_msg("YOU LOSE!");
	}
	if ((game->map.line[line][column] == MAP_EXIT) && (game->map.coins == 0))
	{
			ft_printf(GREEN"YOU WON\n"RESET);
			exit (EXIT_FAILURE);
	}
}

int ft_handle_input(int keysym, t_game *game)
{
	int	column;
	int	line;
	
	column = game->map.player.x;
	line = game->map.player.y;
	if (keysym == KEY_Q || keysym == KEY_ESC)
	{
		//free_game(t_game *game);
		ft_error_msg("Escape key was pressed");
		return (0);
	}
	if (keysym == KEY_UP || keysym == KEY_W)
	{
		game->player_sprite = FRONT;
		ft_player_move(game, --line, column);
	}
	if (keysym == KEY_LEFT || keysym == KEY_A)
	{
		game->player_sprite = LEFT;
		ft_player_move(game, line, --column);
	}
	if (keysym == KEY_RIGHT || keysym == KEY_D)
	{
		game->player_sprite = RIGHT;
		ft_player_move(game, line, ++column);
	}
	if (keysym == KEY_DOWN || keysym == KEY_S)
	{
		game->player_sprite = BACK;
		ft_player_move(game, ++line, column);
	}
	return (0);
}

void ft_init_vars(t_game *game)
{
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.players = 0;
	game->movements = 0;
	game->player_sprite = RIGHT;
}


size_t ft_strlen_line(char *str)
{
	size_t	length;

	length = 0;
	while (str[length] && ft_isprint(str[length]))
		length++;
	return (length);
}

void ft_check_command_line_arguments(int argc, char **argv)
{
	int map_parameter_len;

	if (argc > 10)
		ft_error_msg("Too many arguments (It should be only two).");
	if (argc < 2)
		ft_error_msg("The Map file is missing");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		ft_error_msg("Map file extention is wrong (It should be .ber).");
}

t_bool ft_check_for_invalid_map_parameters(char *line)
{
	int parameter;

	parameter = 0;
	while ((line[parameter]) && ft_isprint(line[parameter]) == true)
	{
		if ((line[parameter] == WALL) 
			|| (line[parameter] == FLOOR)
			|| (line[parameter] == COINS) 
			|| (line[parameter] == MAP_EXIT)
			|| (line[parameter] == PLAYER)
			|| (line[parameter] == TOXIC)
			|| (line[parameter] == SPIKES))
			parameter++;
		else
			return (true);
	}
	return (false);
}

void ft_init_map(t_game *game, char *argv)
{
	char 	*read_str;
	char	*temporary;
	int		map_fd;
	int		i;

	i = 0;
	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("The Map couldn't be opened. Invalid fd");
	read_str = ft_strdup(get_next_line(map_fd));
	if (!read_str)
		ft_error_msg("Allocation failed");
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
	game->map.columns = ft_strlen_line(game->map.line[0]);
}

void ft_set_start_position(t_game *game, char *line, int y)
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

int	line_occurrences(char *str, char c)
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


void	ft_check_map_parameters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.lines)
	{
		if (ft_check_for_invalid_map_parameters(game->map.line[i]) == true)
			ft_error_msg("Not expected map parameter");
		game->map.coins += line_occurrences(game->map.line[i], COINS);
		game->map.exit += line_occurrences(game->map.line[i], MAP_EXIT);
		game->map.players += line_occurrences(game->map.line[i], PLAYER);
		if (game->map.players == 1)
			ft_set_start_position(game, game->map.line[i], i);
		i++;
	}
	if (game->map.coins == 0)
		ft_error_msg("Invalid Map. There are no collectibles!");
	else if (game->map.exit == 0)
		ft_error_msg("Invalid Map. There is no Exit");
	else if (game->map.players != 1)
		ft_error_msg("Invalid Map. Invalid player quantity.");
}

void ft_check_map(t_game *game)
{
	int 	i;

	i = 0;
	while(i < game->map.lines)
	{
		if ((int) ft_strlen_line(game->map.line[i]) != game->map.columns)
			ft_error_msg("The Map must be rectangular!");
		if ((game->map.line[i][0] != WALL)
			|| (game->map.line[i][game->map.columns - 1] != WALL))
			ft_error_msg("The Map must be surrounded by walls! \
				A vertical wall is missing.");
		i++;
	}
	i = 0;
	while (i < game->map.columns)
	{
		if ((game->map.line[0][i] != WALL) 
			|| (game->map.line[game->map.lines - 1][i] != WALL))
			ft_error_msg("The Map must be surrounded by walls! \
				A horizontal wall is missing.");
		i++;
	}
	ft_check_map_parameters(game);
}

t_image	ft_new_sprite(void *mlx, char *path, t_game *game)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	//if (sprite.ptr == NULL)
	//	ft_ft_error_msg(game, RED"ERROR: "GREY"read xpm\n"RESET);
	return (sprite);
}

void ft_render_sprite(t_game *game, t_image sprite, int column, int line)
{
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	sprite.xpm_ptr, column * sprite.x, line * sprite.y);
}

int ft_render_map(t_game game)
{
	int column;
	int line;

	column = 0;
	line = 0;
	while (line < game.map.lines)
	{
		while (column < game.map.columns)
		{
			if (game.map.line[line][column] == WALL)
				ft_render_sprite (&game, game.wall, column, line);
			if (game.map.line[line][column] == FLOOR)
				ft_render_sprite (&game, game.floor, column, line);
			if (game.map.line[line][column] == COINS)
				ft_render_sprite (&game, game.coins, column, line);
			if (game.map.line[line][column] == MAP_EXIT)
				ft_render_sprite (&game, game.exit_closed, column, line);
			if (game.map.line[line][column] == PLAYER)
				ft_render_sprite (&game, game.player_right, column, line);
			if (game.map.line[line][column] == TOXIC)
				ft_render_sprite (&game, game.toxic, column, line);
			if (game.map.line[line][column] == SPIKES)
				ft_render_sprite (&game, game.spikes, column, line);	
			column++;
		}
		column = 0; 
		line++;
	}
	return (0);
	//ft_print_movements(game);
}

void	ft_print_moves(t_game *game)
{
	//
}

void ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		ft_error_msg("Couldn't find mlx pointer. Try it using a VNC.");
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
	game->map.columns * 32, game->map.lines * 32, "so_long");
	if (game->win_ptr == NULL)
		ft_error_msg("Couldn't create the Window.");
}

void ft_init_sprites(t_game *game)
{
	void *mlx;

	mlx = game->mlx_ptr;
	game->wall = ft_new_sprite(mlx, WALL_XPM, game);
	game->floor = ft_new_sprite(mlx, FLOOR_XPM, game);
	game->coins = ft_new_sprite(mlx, COINS_XPM, game);
	game->player_front = ft_new_sprite(mlx, PLAYER_FRONT_XPM, game);
	game->player_left = ft_new_sprite(mlx, PLAYER_LEFT_XPM, game);
	game->player_right = ft_new_sprite(mlx, PLAYER_RIGHT_XPM, game);
	game->player_back = ft_new_sprite(mlx, PLAYER_BACK_XPM, game);
	game->open_exit = ft_new_sprite(mlx, OPEN_EXIT_XPM, game);
	game->exit_closed = ft_new_sprite(mlx, EXIT_CLOSED_XPM, game);
	game->toxic = ft_new_sprite(mlx, TOXIC_XPM, game);
	game->spikes = ft_new_sprite(mlx, SPIKES_XPM, game);
}

void print_assets(t_game *game, char c)
{
	ft_printf("%c", c);
}

void ft_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_closed.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->open_exit.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->spikes.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->toxic.xpm_ptr);
}

void	ft_free_string_array(char **free_me)
{
	char	**free_me_too;

	free_me_too = free_me;
	while (free_me && *free_me)
		free(*free_me++);
	free(free_me_too);
}

void ft_free_all_allocated_memory(t_game *game)
{
	ft_destroy_images(game);
	ft_free_string_array(game->map.line);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	ft_check_command_line_arguments(argc, argv);
	ft_init_vars(game);
	ft_init_map(game, argv[1]);
	ft_check_map(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(*game);
	mlx_hook(game->win_ptr, 3, 1L << 1, ft_handle_input, game);
	mlx_loop_hook(game->mlx_ptr, &ft_handle_no_event, game);
	mlx_expose_hook(game->win_ptr, &ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);
}
