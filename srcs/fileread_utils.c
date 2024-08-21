/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:25:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:33 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

bool	is_valid_orient(int c);
bool	is_empty_line(char *str);
void	is_fd_invalid(int fd, t_data *cub);
int		ft_iswhitespace(int c);
int		jump_whitepaces(char *line);

bool	is_valid_orient(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_empty_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (true);
	i = jump_whitepaces(str);
	if (str[i] == '\n' || str[i] == '\0')
		return (true);
	else
		return (false);
}

void	is_fd_invalid(int fd, t_data *cub)
{
	if (fd < 0)
		ft_error(CANTOPEN, cub);
	return ;
}

int	ft_iswhitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	jump_whitepaces(char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	return (i);
}
