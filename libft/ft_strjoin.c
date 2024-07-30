/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 07:30:22 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/06 17:39:38 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cenas(char *st1, char *st2)
{
	if (!st2 && !st1)
		return (0);
	if (!*st2 && !*st1)
		return (1);
	else if (*st1 && *st2)
		return (ft_strlen(st2) + ft_strlen(st1));
	else if (*st2 && !*st1)
		return (ft_strlen(st2));
	else if (*st1 && !*st2)
		return (ft_strlen(st1));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*st1;
	char			*st2;
	char			*ret;
	size_t			size;
	size_t			i;

	st1 = (char *)s1;
	st2 = (char *)s2;
	size = cenas(st1, st2);
	if (size == 0)
		return (NULL);
	if (size == 1)
		size = 0;
	ret = (char *)malloc(sizeof(char) * size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size && *st1)
		ret[i++] = *st1++;
	while (i < size && *st2)
		ret[i++] = *st2++;
	ret[i] = '\0';
	return (ret);
}
