/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line_arguments.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 07:08:26 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/18 19:48:48 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include "../header/so_long.h"

void check_command_line_arguments(int argc, char **argv)
{
	int map_parameter_len;

	if (argc > 2)
		error_msg("Too many arguments (It should be only two)");
	if (argc < 2)
		error_msg("The Map file is missing");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		error_msg("Map file extention is wrong (It should be .ber)");
}
