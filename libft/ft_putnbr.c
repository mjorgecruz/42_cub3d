/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:56:20 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 17:31:26 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//used in ft_printf()

int	ft_putnbr_fd_pf(int n, int fd)
{
	char	*s;
	int		x;

	x = 0;
	s = ft_itoa_pf(n);
	x = ft_putstr_fd_pf(s, fd);
	free(s);
	return (x);
}
