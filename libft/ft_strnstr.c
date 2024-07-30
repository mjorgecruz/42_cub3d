/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:09:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/05 00:47:44 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len2;

	if (!*s2)
		return ((char *)s1);
	len2 = ft_strlen(s2);
	while (*s1 && n >= len2)
	{
		if (*s1 == *s2 && ft_strncmp(s1, s2, len2) == 0)
		{
			return ((char *)s1);
		}
		s1++;
		n--;
	}
	return (NULL);
}
