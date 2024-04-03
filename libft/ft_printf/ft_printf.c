/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:49:11 by amalgonn          #+#    #+#             */
/*   Updated: 2024/01/10 14:34:24 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	check_type(const char *input, va_list arg)
{
	int	i;

	i = 0;
	if (*input == 'c')
		i += print_char(va_arg(arg, int));
	else if (*input == 's')
		i += print_string(va_arg(arg, char *));
	else if (*input == 'd' || *input == 'i')
		i += print_num(va_arg(arg, int));
	else if (*input == 'u' )
		i += putnbr_base(va_arg(arg, unsigned int), "0123456789");
	else if (*input == 'x')
		i += putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef");
	else if (*input == 'X')
		i += putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF");
	else if (*input == 'p')
		i += print_ptr(va_arg(arg, unsigned long), "0123456789abcdef");
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;

	i = 0;
	if (!input)
		return (-1);
	va_start (args, input);
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			if (ft_strchr("cspdiuxX", *input))
				i += check_type(input, args);
			else if (*input == '%')
				i += print_char('%');
		}
		else
			i += print_char(*input);
		input++;
	}
	va_end(args);
	return (i);
}
