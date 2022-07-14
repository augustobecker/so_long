/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:04:37 by acesar-l          #+#    #+#             */
/*   Updated: 2022/07/14 03:15:50 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "..//Libft/libft.h"

# define IMG_HEIGHT			32
# define IMG_WIDTH			32

# define WALL				'1'
# define FLOOR 				'0'
# define COINS  			'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364

# define KEY_Q				113
# define KEY_ESC  			65307

# define FRONT				1
# define LEFT				2
# define RIGHT				3
# define BACK				4

# define WALL_XPM			"assets/sprites/wall.xpm"
# define FLOOR_XPM			"assets/sprites/floor.xpm"
# define COINS_XPM			"assets/sprites/coin-bag.xpm"
# define PLAYER_FRONT_XPM	"assets/sprites/player/front.xpm"
# define PLAYER_LEFT_XPM	"assets/sprites/player/left.xpm"
# define PLAYER_RIGHT_XPM	"assets/sprites/player/right.xpm"
# define PLAYER_BACK_XPM	"assets/sprites/player/back.xpm"
# define OPEN_EXIT_XPM		"assets/sprites/open-exit.xpm"
# define EXIT_CLOSED_XPM	"assets/sprites/exit-closed.xpm"

# define GREEN				"\033[0;32m"
# define RED 				"\033[1;31m"
# define GREY 				"\033[0;90m"
# define CYAN				"\033[1;96m"
# define RESET 				"\033[0m"

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
	char		**full;
	int			rows;
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
	t_bool		map_alloc;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		open_exit;
	t_image		exit_closed;
	t_image		player_front;
	t_image		player_left;
	t_image		player_right;
	t_image		player_back;
}	t_game;

void	ft_check_command_line_arguments(int argc, char **argv, t_game *game);
void	ft_init_map(t_game *game, char *argv);
t_bool	ft_check_for_empty_line(char *map);
void	ft_init_vars(t_game *game);
void	ft_check_map(t_game *game);
void	ft_check_rows(t_game *game);
void	ft_check_columns(t_game *game);
void	ft_count_map_parameters(t_game *game);
void	ft_verify_map_parameters(t_game *game);
void	ft_init_mlx(t_game *game);
void	ft_init_sprites(t_game *game);
t_image	ft_new_sprite(void *mlx, char *path, t_game *game);
int		ft_render_map(t_game *game);
void	ft_identify_sprite(t_game *game, int x, int y);
void	ft_render_player(t_game *game, int x, int y);
void	ft_render_sprite(t_game *game, t_image sprite, int column, int line);
int		ft_handle_input(int keysym, t_game *game);
void	ft_player_move(t_game *game, int x, int y, int player_sprite);
int		ft_error_msg(char *message, t_game *game);
int		ft_close_game(t_game *game);
void	ft_print_movements(t_game *game);
int		ft_victory(t_game *game);
int		exit_click(t_game *game);
void	ft_free_all_allocated_memory(t_game *game);
void	ft_destroy_images(t_game *game);
void	ft_free_string(char **free_str);
void	ft_free_map(t_game *game);

char	*ft_strappend(char **s1, const char *s2);

int main(int argc, char	**argv)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	ft_check_command_line_arguments(argc, argv, game);
	ft_init_map(game, argv[1]);
	ft_init_vars(game);
	ft_check_map(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game, game);
	mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);
}

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

t_bool ft_check_for_empty_line(char *map)
{
	int i;
	
	i = 1;
	if (map[0] == '\n')
	{
		free(map);
		return (true);
	}
	else if (map[ft_strlen(map)] - 1 == '\n')
	{
		free(map);
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

void	ft_init_vars(t_game *game)
{
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.players = 0;
	game->movements = 0;
	game->map.columns = ft_strlen(game->map.full[0]);
	game->player_sprite = RIGHT;
}

void	ft_check_map(t_game *game)
{
	ft_check_rows(game);
	ft_check_columns(game);
	ft_count_map_parameters(game);
	ft_verify_map_parameters(game);
}

void	ft_check_rows(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if ((int) ft_strlen(game->map.full[i]) != game->map.columns)
			ft_error_msg("Invalid Map. The Map must be rectangular!", game);		
		else if (game->map.full[i][0] != WALL)
			ft_error_msg("Invalid Map. \
There's a Wall missing from the first row.\n\
The Map must be surrounded by walls!.", game);
		else if (game->map.full[i][game->map.columns - 1] != WALL)
			ft_error_msg("Invalid Map. \
There's a Wall missing from the last row.\n\
The Map must be surrounded by walls!.", game);
		i++;
	}
}

void	ft_check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.full[0][i] != WALL)
			ft_error_msg("Invalid Map. \
There's a Wall missing from the first column.\n\
The Map must be surrounded by walls!.", game);
		else if (game->map.full[game->map.rows - 1][i] != WALL)
			ft_error_msg("Invalid Map. \
There's a Wall missing from the last column.\n\
The Map must be surrounded by walls!.", game);
		i++;
	}
}

void	ft_count_map_parameters(t_game *game)
{
	int	x;
	int y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			if (!ft_strchr("CEP01", game->map.full[y][x]))
				ft_error_msg("Invalid Map. Not expected map parameter.", game);
			else if (game->map.full[y][x] == PLAYER)
			{
				game->map.players++;
				game->map.player.x = x;
				game->map.player.y = y;
			}
			else if (game->map.full[y][x] == COINS)
				game->map.coins++;
			else if (game->map.full[y][x] == MAP_EXIT)
				game->map.exit++;
			x++;
		}
		y++;
	}
}

void	ft_verify_map_parameters(t_game *game)
{
	if (game->map.coins == 0)
		ft_error_msg("Invalid Map. There are no Coins!", game);
	else if (game->map.exit == 0)
		ft_error_msg("Invalid Map. There is no Exit.", game);
	else if (game->map.players != 1)
		ft_error_msg("Invalid Map. Invalid Player quantity. \
It's a single player game.", game);
}

int	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			ft_identify_sprite(game, y, x);
			x++;
		}
		y++;
	}
	ft_print_movements(game);
	return (0);
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		ft_error_msg("Couldn't find mlx pointer. Try it using a VNC.", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
	game->map.columns * IMG_WIDTH, game->map.rows * IMG_HEIGHT, "so_long");
	if (game->win_ptr == NULL)
	{
		free(game->mlx_ptr);
		ft_error_msg("Couldn't create the Window.", game);
	}
}

void ft_init_sprites(t_game *game)
{
	void	*mlx;

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
}

t_image	ft_new_sprite(void *mlx, char *path, t_game *game)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		ft_error_msg("Couldn't find a sprite. Does it exist?", game);
	return (sprite);
}

void	ft_identify_sprite(t_game *game, int y, int x)
{	
	char	parameter;
	
	parameter = game->map.full[y][x];
	if (parameter == WALL)
		ft_render_sprite (game, game->wall, y, x);
	else if (parameter == FLOOR)
		ft_render_sprite (game, game->floor, y, x);
	else if (parameter == COINS)
		ft_render_sprite (game, game->coins, y, x);
	else if (parameter == MAP_EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite (game, game->open_exit, y, x);
		else
			ft_render_sprite (game, game->exit_closed, y, x);
	}
	else if (parameter == PLAYER)
		ft_render_player (game, y, x);
}

void	ft_render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		ft_render_sprite (game, game->player_front, y, x);
	if (game->player_sprite == LEFT)
		ft_render_sprite (game, game->player_left, y, x);
	if (game->player_sprite == RIGHT)
		ft_render_sprite (game, game->player_right, y, x);
	if (game->player_sprite == BACK)
		ft_render_sprite (game, game->player_back, y, x);
}

void	ft_render_sprite(t_game *game, t_image sprite, int line, int column)
{
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	sprite.xpm_ptr, column * sprite.x, line * sprite.y);
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		ft_player_move(game, game->map.player.y - 1, game->map.player.x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		ft_player_move(game, game->map.player.y, game->map.player.x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		ft_player_move(game, game->map.player.y, game->map.player.x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		ft_player_move(game, game->map.player.y + 1, game->map.player.x, FRONT);
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	return (0);
}

void	ft_player_move(t_game *game, int new_y, int new_x, int player_sprite)
{
	int	last_x;
	int last_y;

	game->player_sprite = player_sprite;
	last_x = game->map.player.x;
	last_y = game->map.player.y;
	if (game->map.full[new_y][new_x] == MAP_EXIT && game->map.coins == 0)
		ft_victory(game);
	else if ((game->map.full[new_y][new_x] == FLOOR)
	|| (game->map.full[new_y][new_x] == COINS))
	{
		game->map.full[last_y][last_x] = FLOOR;
		if (game->map.full[new_y][new_x] == COINS)
			game->map.coins--;
		game->map.player.x = new_x;
		game->map.player.y = new_y;
		game->map.full[new_y][new_x] = PLAYER;
		game->movements++;
		ft_render_map(game);
	}
}

int ft_error_msg(char *message, t_game *game)
{
	free(game);
	if (game->map_alloc == true)
		ft_free_map(game);
	ft_printf(RED"Error\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}

int	ft_close_game(t_game *game)
{
	ft_printf(CYAN"Movements: %d\n"RESET, game->movements);
	ft_free_all_allocated_memory(game);	
	ft_printf(GREY"CLOSED\n"RESET);
	exit (EXIT_FAILURE);
}

int	ft_victory(t_game *game)
{
	ft_printf(CYAN"\n			Movements: %d\n"RESET, ++game->movements);
	ft_free_all_allocated_memory(game);
	ft_printf(GREEN"\n\
██████████████████████████████████████████████████████████████████\n\
██                                                              ██\n\
██  ███  ███  ██████  ██    ██     ██      ██ ██ ██    ██   ██  ██\n\
██   ██  ██  ██    ██ ██    ██     ██      ██ ██ ███   ██   ██  ██\n\
██    ████   █      █ ██    ██     ██  ██  ██ ██ ██ ██ ██   ██  ██\n\
██     ██    ██    ██ ██    ██     ██ ████ ██ ██ ██  ████       ██\n\
██     ██     ██████    ████        ███  ███  ██ ██   ███   ██  ██\n\
██                                                              ██\n\
██████████████████████████████████████████████████████████████████\n\n\
"RESET);
	exit (EXIT_FAILURE);
}

void	ft_print_movements(t_game *game)
{
	char	*movements;
	char	*phrase;
	int		i;

	i = 0;
	while (i < game->map.columns)
		ft_render_sprite (game, game->wall, 0, i++);
	movements = ft_itoa(game->movements);
	phrase = ft_strjoin("Movements : ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 99999, phrase);
	free(movements);
	free(phrase);
}

void ft_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->coins.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_closed.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->open_exit.xpm_ptr);
}

void	ft_free_map(t_game *game)
{
	int	string;

	string = 0;
	while (string < game->map.rows)
		free(game->map.full[string++]);
	free(game->map.full);
}

void ft_free_all_allocated_memory(t_game *game)
{
	ft_destroy_images(game);
	ft_free_map(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

char	*ft_strappend(char **s1, const char *s2)
{
	char	*str;

	if (!*s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(*s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(str, s2, ft_strlen(*s1) + ft_strlen(s2) + 1);
	free(*s1);
	return (str);
}
