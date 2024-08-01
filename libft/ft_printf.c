/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:04:02 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 18:36:00 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//used in ft_printf()

int	ft_printf(const char *input, ...)
{
	int		i;
	va_list	list;

	va_start(list, input);
	i = 0;
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			if (*input != '%' && *input)
			{
				i += ft_typefinder_pf(*input, list);
			}
			else
				i += ft_putchar_fd_pf(*input, 1);
		}
		else
			i += ft_putchar_fd_pf(*input, 1);
		input++;
	}
	va_end(list);
	return (i);
}
