/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reversed_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 03:58:01 by acesar-l          #+#    #+#             */
/*   Updated: 2022/02/22 03:58:01 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_print_reversed_str(char *str)
{
int	i;
int	bytes;

bytes = ft_strlen(str);
i = bytes - 1;
while (i >= 0)
	write(1, &str[i--], sizeof(char) * 1);
return (bytes);
}
