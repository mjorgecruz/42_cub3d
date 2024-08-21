/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:23:33 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:45 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

bool	is_xpm_file(char *xpm);
bool	compare_id_xpm(char *xpm);
bool	check_texture_match(char *xpm);
bool	check_texture_str(char *xpm);
void	check_xpm_format(t_data *cub);

bool	is_xpm_file(char *xpm)
{
	int	i;

	i = 0;
	while (xpm[i])
	{
		if (xpm[i] == '.')
		{
			if (!ft_strncmp(&xpm[i], ".xpm", 4))
			{
				if (is_empty_line(&xpm[i] + 4))
					return (true);
			}
			else
				return (false);
		}
		i++;
	}
	return (false);
}

bool	compare_id_xpm(char *xpm)
{
	if (!xpm)
		return (false);
	else if (!ft_strncmp(xpm, "south", 5))
		return (true);
	else if (!ft_strncmp(xpm, "north", 5))
		return (true);
	else if (!ft_strncmp(xpm, "east", 4))
		return (true);
	else if (!ft_strncmp(xpm, "west", 4))
		return (true);
	return (false);
}

bool	check_texture_match(char *xpm)
{
	int	i;
	int	marker;

	marker = 0;
	i = -1;
	while (xpm[++i])
	{
		if (xpm[i] == '/')
			marker = i + 1;
	}
	if (!is_xpm_file(xpm + marker))
		return (false);
	return (true);
}

bool	check_texture_str(char *xpm)
{
	int	i;

	if (!xpm || is_empty_line(xpm))
		return (false);
	i = 0;
	while (xpm[i])
	{
		if (ft_iswhitespace(xpm[i]))
		{
			while (xpm[++i])
			{
				if (!ft_iswhitespace(xpm[i]))
					return (false);
			}
		}
		if (xpm[i])
			i++;
	}
	if (!check_texture_match(xpm))
		return (false);
	return (true);
}

void	check_xpm_format(t_data *cub)
{
	if (!check_texture_str(cub->north))
		ft_error(IVALIDMAP, cub);
	else if (!check_texture_str(cub->east))
		ft_error(IVALIDMAP, cub);
	else if (!check_texture_str(cub->south))
		ft_error(IVALIDMAP, cub);
	else if (!check_texture_str(cub->west))
		ft_error(IVALIDMAP, cub);
}
