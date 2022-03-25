/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:19:25 by acesar-l          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:27 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

size_t strlen_line(char *str)
{
	size_t	length;

	length = 0;
	while ((str[length]) && (ft_isprint(str[length]) == TRUE))
		length++;
	return (length);
}
