/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:20:12 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 18:42:00 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//used in ft_printf()

int	ft_putptr_pf(unsigned long long num, int fd)
{
	int					x;

	x = 0;
	if (num == 0)
		return (write (fd, "0", 1));
	if (num < 16)
	{
		return (write (fd, &"0123456789abcdef"[num], 1));
	}
	else
	{
		x += ft_putptr_pf(num / 16, fd);
		x += ft_putptr_pf(num % 16, fd);
	}
	return (x);
}

int	ft_putptr0x_pf(unsigned long long num, int fd)
{
	write (fd, "0", 1);
	write (fd, "x", 1);
	return ((ft_putptr_pf(num, fd) + 2));
}
