/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:47:45 by acesar-l          #+#    #+#             */
/*   Updated: 2022/04/11 19:47:46 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int handle_input(int keysym, t_game *game)
{
	int	line;
	int	column;
	
	line = game->map.player_pos.x;
	column = game->map.player_pos.y;
	if (keysym == KEY_Q || keysym == KEY_ESC)
		free_game(t_game *game);
	if (keysym == KEY_UP || keysym == KEY_W)
		player_move(game, line, --column);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		player_move(game, --line, column);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		player_move(game, ++line, column);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		player_move(game, line, ++column);
	return (0);
}
