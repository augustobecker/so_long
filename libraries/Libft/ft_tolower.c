/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:55:00 by acesar-l          #+#    #+#             */
/*   Updated: 2021/09/07 16:55:01 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int argument)
{
	if (argument >= 'A' && argument <= 'Z')
		argument += 32;
	return (argument);
}
