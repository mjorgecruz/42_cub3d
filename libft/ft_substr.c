/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:35:25 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/05 22:56:41 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < n)
		n = size;
	sub = (char *)malloc(sizeof(char) * (n + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, (n + 1));
	return (sub);
}
