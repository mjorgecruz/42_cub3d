/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 16:34:52 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIN_W && y < WIN_H && x > 0 && y > 0) 
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	render_point_player(t_data *img, int pos_x, int pos_y)
{
    int     color;

	color = 0x305060;
	pixel_put(img, pos_x, pos_y, color);
	pixel_put(img, pos_x + 1, pos_y, color);
	pixel_put(img, pos_x - 1, pos_y, color);
	pixel_put(img, pos_x, pos_y + 1, color);
	pixel_put(img, pos_x, pos_y - 1, color);
}

void	render_rect_wall(t_data *img, int pos_x, int pos_y)
{
	int		i;
	int		j;
    int     color;

	i = pos_x * 5;
	j = pos_y * 5;
	while (i < pos_x * 5 + 5)
	{
		j = 0;
		while (j < pos_y * 5 + 5)
		{
			color = 0x305060;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	render_rect_ground(t_data *img, int pos_x, int pos_y)
{
	int		i;
	int		j;
    int     color;

	i = pos_x * 5;
	j = pos_y * 5;
	while (i < pos_x * 5 + 5)
	{
		j = 0;
		while (j < pos_y * 5 + 5)
		{
			color = 0x000000;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}



