/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:39:11 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 17:25:12 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//used in ft_printf()

char	*ft_itoa_pf(int n)
{
	char			*s;
	long int		size;
	unsigned int	aux;

	size = countnbr_pf(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (0);
	s[size--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		aux = n * -1;
		s[0] = '-';
	}
	else
		aux = n;
	s = set_nbr_str_pf(aux, s, size);
	return (s);
}
