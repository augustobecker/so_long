/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:53:38 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/22 19:26:58 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include "libft.h"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool

typedef struct s_map
{
	char	**line;
	int		nbr_lines;
	int		line_len;
	int 	coins;
	int 	map_exit;
	int 	start_pos;
}	t_map

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int 	movements;
	t_map	map;
}	t_game

void	check_command_line_arguments(int argc, char **argv);
void	init_map(t_game *game, char *argv);
void	check_map(t_game *game);
void	check_map_parameters(t_game *game);
t_bool	check_for_invalid_map_parameters(char *line);
int		error_msg(char *message);
void	init_vars(t_game game);

#endif
