/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:58:53 by acesar-l          #+#    #+#             */
/*   Updated: 2021/09/10 19:22:42 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nblength(long int nb);

static	char	*ft_rev_str(char *str);

char	*ft_itoa(int nb)
{
	int			i;
	long int	sign;
	long int	nbr;
	char		*str;

	i = 0;
	sign = 0;
	nbr = (long int)nb;
	str = (char *)ft_calloc((ft_nblength(nbr) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nbr == 0)
		str[i++] = '0';
	if (nbr < 0)
		nbr *= --sign;
	while (nbr > 0)
	{
		str[i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	return (str = ft_rev_str(str));
}

static	int	ft_nblength(long int nb)
{
	int	length;

	length = 0;
	if (nb <= 0)
		length++;
	while (nb)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

static	char	*ft_rev_str(char *str)
{
	int	start;
	int	final;

	start = 0;
	final = ft_strlen(str) - 1;
	while (start < final - start)
	{
		str[start] = str[start] ^ str[final - start];
		str[final - start] = str[start] ^ str[final - start];
		str[start] = str[start] ^ str[final - start];
		start++;
	}
	return (str);
}
