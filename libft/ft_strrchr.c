/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:07:20 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/08 15:07:48 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = 0;
	while (*s)
	{
		if ((char)c == *s)
			p = s;
		s++;
	}
	if ((char)c == 0 && (char)c == *s)
		return ((char *)s);
	return ((char *)p);
}
