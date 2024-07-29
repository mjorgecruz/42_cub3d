/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 23:03:42 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	color = 0xFFFFFF;
	pixel_put(img, pos_x * 50, pos_y * 50, color);
	pixel_put(img, pos_x * 50 + 1, pos_y * 50, color);
	pixel_put(img, pos_x * 50 - 1, pos_y * 50, color);
	pixel_put(img, pos_x * 50, pos_y * 50 + 1, color);
	pixel_put(img, pos_x * 50, pos_y * 50 - 1, color);
}

void	render_rect_wall(t_data *img, int pos_x, int pos_y)
{
	int		i;
	int		j;
    int     color;

	i = pos_x * 50;
	j = pos_y * 50;
	while (i < pos_x * 50 + 50)
	{
		j = pos_y * 50;
		while (j < pos_y * 50 + 50)
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

	i = pos_x * 50;
	j = pos_y * 50;
	while (i < pos_x * 50 + 50)
	{
		j = pos_y * 50;
		while (j < pos_y * 50 + 50)
		{
			color = 0x000000;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

int minimaper(t_data *cub)
{
	int		x;
	int		y;
	int map[4][4] = {{1,1, 1, 1},{1, 0, 0, 1}, {1, 0, 9, 1}, {1, 1, 1, 1}};
	
	y = 0;
	x = 0;
	
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (map[x][y] == 1)
				render_rect_wall(cub, x, y);
			else if (map[x][y] == 0)
				render_rect_ground(cub, x, y);
			else
				render_point_player(cub, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
	return (1);
}

