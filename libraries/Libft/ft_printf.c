/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:17:35 by acesar-l          #+#    #+#             */
/*   Updated: 2021/12/28 21:10:31 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_arguments(va_list arg, char c)
{
	int	bytes;

	bytes = 0;
	if (c == '%')
		bytes += ft_argument_percent();
	if (c == 'c')
		bytes += ft_argument_c(va_arg(arg, int));
	if (c == 's')
		bytes += ft_argument_s(va_arg(arg, char *));
	if (c == 'p')
		bytes += ft_argument_p(va_arg(arg, unsigned long));
	if (c == 'd' || c == 'i')
		bytes += ft_arguments_d_i(va_arg(arg, int));
	if (c == 'u')
		bytes += ft_argument_u(va_arg(arg, int));
	if (c == 'x' || c == 'X')
		bytes += ft_arguments_x(va_arg(arg, unsigned int), c);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	va_list		arg;
	int		i;
	int		bytes;
	char		c;

	i = 0;
	bytes = 0;
	va_start(arg, str);
	while (str[i])
	{
		c = str[i + 1];
		if (str[i] == '%')
		{
			bytes += ft_check_arguments(arg, c);
			i++;
		}
		else
			bytes += write(1, &str[i], sizeof(char));
		i++;
	}
	va_end(arg);
	return (bytes);
}
