/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:16:12 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/21 15:40:53 by acesar-l         ###   ########.fr       */
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

# define ERROR 		-1

# define WALL 		'1'
# define EMPTY_SPC	'0'
# define COIN 		'C'
# define MAP_EXIT 	'E'
# define START_POS	'P'

# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define RESET "\033[0m"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 300

#define SUCESS	 	  0
#define MLX_ERROR 	  1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

typedef struct s_map
{
	int		fd;
	int		nbr_lines;
	int		line_len;
	char	**line;
}	t_map;

typedef struct s_game
{
	int coin;
	int map_exit;
	int start_pos;
}	t_game;

typedef struct s_image
{
	void	*img_ptr;
} t_image;

int handle_no_event(void *data)
{
	return (0);
}

int handle_input(int keysym, t_data *data)
{
	if ( keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	ft_printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	error_msg(char *message)
{
	ft_printf(RED"Error\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}

int	are_mapparamenters(char *line)
{
	int parameter;

	parameter = 0;
	while (line[parameter])
	{
		if ((line[parameter] == WALL) 
			|| (line[parameter] == EMPTY_SPC)
			|| (line[parameter] == COIN) 
			|| (line[parameter] == MAP_EXIT)
			|| (line[parameter] == START_POS))
			parameter++;
		else
			return (0);
	}
	return (1);
}

int	init_map(t_map *map, char *argv)
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

void	are_mapparameters_present(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	game->coin = 0;
	game->map_exit = 0;
	game->start_pos = 0;
	while (i <= map->nbr_lines)
	{
		if (!are_mapparamenters(map->line[i]))
			error_msg("Not expected map parameter");
		game->coin += ft_count_occurrences(map->line[i], COIN);
		game->map_exit += ft_count_occurrences(map->line[i], MAP_EXIT);
		game->start_pos += ft_count_occurrences(map->line[i], START_POS);
		i++;
	}
	if (!game->coin)
		error_msg("There are no collectibles");
	if (!game->map_exit)
		error_msg("There are no Exit");
	if (game->start_pos != 1)
		error_msg("Invalid player quantity");
}

void	check_map(t_map *map, t_game *game)
{
	int 	i;

	i = 0;
	if (map->nbr_lines == map->line_len)
		error_msg("Square Map. The Map must be rectangular!");
	while(i <= map->nbr_lines)
	{
		if ((int) ft_strlen(map->line[i]) != map->line_len)
			error_msg("The Map must be rectangular!");
		if (map->line[i][0] != WALL || map->line[i][map->line_len - 1] != WALL)
			error_msg("The Map must be surrounded by walls! Missing vertical wall");
		i++;
	}
	i = 0;
	while (map->line[0][i])
	{
		if (map->line[0][i] != WALL || map->line[map->nbr_lines][i] != WALL)
			error_msg("The Map must be surrounded by walls! Missing horizontal wall");
		i++;
	}
	are_mapparameters_present(map, game);
}

void	check_arguments(int argc, char **argv)
{
	int map_parameter_len;

	if (argc > 2)
		error_msg("Too many arguments");
	if (argc < 2)
		error_msg("Map file is missing");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		error_msg("Map file extention is wrong (It should be .ber)");
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;
	t_data 	data;
	//t_image	coin_bag;
	int		i;

	check_arguments(argc, argv);
	init_map(&map, argv[1]);
	check_map(&map, &game);
	i = 0;
	while (i < 5)
		ft_putendl_fd(map.line[i++], 1);

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	
	mlx_pixel_put(data.mlx_ptr, data.win_ptr, 640/2, 360/2, 0xFFFFFF); 																			//draw a pixel
	mlx_string_put (data.mlx_ptr, data.win_ptr, WINDOW_WIDTH/4 , WINDOW_HEIGHT/4, 0xFFFFFF, "What Muggles are only able to do accidentally:)");	//put a string on the screeen
	mlx_string_put (data.mlx_ptr, data.win_ptr, WINDOW_WIDTH/4 , WINDOW_HEIGHT - 30, 0xFFFFFF, "42sp");											//put a string on the screeen

	//coin_bag.img_ptr = mlx_new_image (data.mlx_ptr, ); //image manipulation
	//mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, coin_bag.img_ptr);
	
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr); //Loop - nenhuma parte do projeto deve vir após isso - apenas o free
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
