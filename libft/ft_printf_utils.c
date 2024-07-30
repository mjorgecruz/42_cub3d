/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:06:11 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 18:34:47 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//used in ft_printf()

int	ft_num_len_pf(unsigned	int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

int	countnbr_pf(int c)
{
	int	size;

	size = 0;
	if (c <= 0)
		size = 1;
	while (c)
	{
		c = c / 10;
		size++;
	}
	return (size);
}

char	*set_nbr_str_pf(unsigned int aux, char *s, long int size)
{
	while (aux > 0)
	{
		s[size--] = (aux % 10) + '0';
		aux = aux / 10;
	}
	return (s);
}

int	ft_putchar_fd_pf(char c, int fd)
{
	return (write (fd, &c, 1));
}
