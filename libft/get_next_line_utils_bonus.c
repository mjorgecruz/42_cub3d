/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:58:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 18:42:07 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mem_alloc(size_t nmemb, size_t size)
{
	char	*ptr;
	int		i;
	int		n;

	i = 0;
	n = nmemb * size;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (n--)
		ptr[i++] = '\0';
	return (ptr);
}

int	ft_findnl(char *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	while (ptr[i])
	{
		if (ptr[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strleng(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_add_nest(char *nest, char *buffer)
{
	char	*temp;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (!nest)
		nest = ft_mem_alloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	size = ft_strleng(nest) + ft_strleng(buffer);
	temp = ft_mem_alloc((size + 1), sizeof(char));
	while (nest[i])
	{
		temp[i] = nest[i];
		i++;
	}
	while (buffer[j])
		temp[i++] = buffer[j++];
	free(nest);
	return (temp);
}
