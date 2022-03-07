/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_converter_to_hex.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:13:28 by acesar-l          #+#    #+#             */
/*   Updated: 2022/02/18 21:03:25 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_decimal_converter_to_hex(char digit, char type)
{
	int	capitalize;

	capitalize = 0;
	if (type == 'X')
		capitalize = 32;
	if (digit > 9)
	{
		if (digit == 10)
			return ('a' - capitalize);
		if (digit == 11)
			return ('b' - capitalize);
		if (digit == 12)
			return ('c' - capitalize);
		if (digit == 13)
			return ('d' - capitalize);
		if (digit == 14)
			return ('e' - capitalize);
		if (digit == 15)
			return ('f' - capitalize);
	}
	else
		return (digit + '0');
	return (0);
}
