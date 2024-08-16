/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_renders_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:22 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 00:32:56 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	render_point_player(t_data *img, double pos_x, double pos_y)
{
	int     color;

	color = 0xFFFFFF;
	pixel_put(img, (int) pos_x, (int) pos_y, color);
	pixel_put(img, (int) pos_x + 1, (int)pos_y, color);
	pixel_put(img, (int) pos_x - 1, (int) pos_y , color);
	pixel_put(img, (int) pos_x, (int) pos_y + 1, color);
	pixel_put(img, (int) pos_x, (int) pos_y - 1, color);
}

void	render_rect_wall(t_data *img, int pos_x, int pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = pos_x * scale;
	j = pos_y * scale;

	while (i < pos_x * scale + scale - 1)
	{
		j = pos_y * scale;
		while (j < pos_y * scale + scale - 1)
		{
			color = 0x305060;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	render_rect_ground(t_data *img, int pos_x, int pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = pos_x * scale;
	j = pos_y * scale;
	while (i < pos_x * scale + scale)
	{
		j = pos_y * scale;
		while (j < pos_y * scale + scale)
		{
			color = 0x000000;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	render_rect_door(t_data *img, double pos_x, double pos_y, int scale)
{
	int door_num;
	
	door_num = search_door(img, pos_x, pos_y);
	render_rect_ground(img, (int) pos_x, (int) pos_y, scale);
	if (img->doors[door_num].open == false)
	{
		if (img->doors[door_num].orientation == 1)
			render_h_door(img, img->doors[door_num].pos_x, img->doors[door_num].pos_y, scale);
		else if (img->doors[door_num].orientation == 0)
			render_v_door(img, img->doors[door_num].pos_x, img->doors[door_num].pos_y, scale);
	}	
}

void	render_h_door(t_data *img, double pos_x, double pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = (int) (pos_x * (double) scale - (double) scale / 5);
	j = (int) pos_y * scale;

	while (i < (int) (pos_x * (double) scale + (double) scale / 5))
	{
		j = (int) pos_y * scale;
		while (j < (int) pos_y * scale + scale - 1)
		{
			color = 0x30FF60;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	render_v_door(t_data *img, double pos_x, double pos_y, int scale)
{
		int		i;
	int		j;
	int     color;

	i = (int) pos_x * scale;
	j = (int) (pos_y * (double) scale - (double) scale / 5);
	while (i < (int) pos_x * scale + scale - 1)
	{
		j = (int) (pos_y * (double) scale - (double) scale / 5);
		while (j < (int) (pos_y * (double) scale + (double) scale / 5))
		{
			color = 0x305060;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
