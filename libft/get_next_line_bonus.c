/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:57:46 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/11/10 18:42:10 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_newline(char *nest)
{
	char	*temp;
	int		i;

	if (!*nest)
		return (NULL);
	i = 0;
	while (nest[i] && nest[i] != '\n')
		i++;
	temp = ft_mem_alloc(i + 2, sizeof(char));
	i = 0;
	while (nest[i] && nest[i] != '\n')
	{
		temp[i] = nest[i];
		i++;
	}
	temp[i] = nest[i];
	return (temp);
}

char	*get_rest(char *nest)
{
	char	*temp;
	int		i;
	int		index;

	index = 0;
	i = 0;
	while (nest[i] && nest[i] != '\n')
		i++;
	if (!nest[i])
	{
		free(nest);
		return (NULL);
	}
	temp = ft_mem_alloc(ft_strleng(nest) - i + 1, sizeof(char));
	while (nest[i])
		temp[index++] = nest[++i];
	temp[index] = '\0';
	free(nest);
	return (temp);
}

void	*ft_clean(char **nest, char **buffer)
{
	free(*buffer);
	free(*nest);
	*nest = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	int				read_count;
	char			*buffer;
	char			*line;
	static char		*nest[FOPEN_MAX];

	read_count = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	buffer = ft_mem_alloc(BUFFER_SIZE + 1, sizeof(char));
	while (!(ft_findnl(buffer)) && read_count != 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == -1)
			return (ft_clean(&nest[fd], &buffer));
		buffer[read_count] = '\0';
		nest[fd] = ft_add_nest(nest[fd], buffer);
	}
	line = get_newline(nest[fd]);
	nest[fd] = get_rest(nest[fd]);
	free(buffer);
	return (line);
}
