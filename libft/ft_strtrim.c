/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 07:32:28 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/08 15:45:05 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]) && i < size)
		i++;
	if (i == size)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[size - 1]) && size)
		size--;
	return (ft_substr(s1, i, (size - i)));
}
