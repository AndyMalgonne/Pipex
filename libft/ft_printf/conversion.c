/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:06:03 by amalgonn          #+#    #+#             */
/*   Updated: 2024/01/10 14:34:11 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_string(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

static int	count_num(int n)
{
	int				i;
	unsigned int	y;

	i = 0;
	y = n;
	if (n < 0)
	{
		y = -n;
		i++;
	}
	while (y > 9)
	{
		y /= 10;
		i++;
	}
	return (++i);
}

int	print_num(int nb)
{
	ft_putnbr_fd(nb, 1);
	return (count_num(nb));
}
