/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:13:39 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:58:47 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	render_v_door(t_data *img, int door_num, int scale);

void	render_v_door(t_data *img, int door_num, int scale)
{
	int		i;
	int		j;
	int		color;

	i = (int)img->doors[door_num].pos_x * scale;
	j = (int)(img->doors[door_num].pos_y * \
		(double)scale - (double)scale / 5);
	if (img->doors[door_num].open == false)
		color = 0xFF1060;
	else
		color = 0x30FF60;
	while (i < (int)img->doors[door_num].pos_x * scale + scale - 1)
	{
		j = (int)(img->doors[door_num].pos_y * \
			(double)scale - (double)scale / 5);
		while (j < (int)(img->doors[door_num].pos_y * \
			(double)scale + (double)scale / 5))
		{
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
