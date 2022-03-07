/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:19:12 by acesar-l          #+#    #+#             */
/*   Updated: 2021/09/07 17:22:21 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	sum;

	sum = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		if (n == -2147483648)
		{
			n--;
			sum = 1;
		}
	}
	if (n < 10)
		ft_putchar_fd(n + '0' + sum, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10 + sum, fd);
	}
}
