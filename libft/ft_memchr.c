/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:09:15 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/08 12:18:27 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	ci;

	s1 = (unsigned char *)s;
	ci = (unsigned char)c;
	while (n--)
	{
		if (*s1 == ci)
			return ((void *)s1);
		s1++;
	}
	return (NULL);
}
//	if (!n)
//		return (NULL); this was before the while loop