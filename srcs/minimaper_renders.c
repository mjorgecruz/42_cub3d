/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_renders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:22 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 10:52:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_point_player(t_data *img, double pos_x, double pos_y);
void	render_rect_wall(t_data *img, int pos_x, int pos_y, int scale);
void	render_rect_ground(t_data *img, int pos_x, int pos_y, int scale);

void	render_point_player(t_data *img, double pos_x, double pos_y)
{
	int	color;

	color = 0xFFFFFF;
	pixel_put(img, (int) pos_x, (int) pos_y, color);
	pixel_put(img, (int) pos_x + 1, (int)pos_y, color);
	pixel_put(img, (int) pos_x - 1, (int) pos_y, color);
	pixel_put(img, (int) pos_x, (int) pos_y + 1, color);
	pixel_put(img, (int) pos_x, (int) pos_y - 1, color);
}

void	render_rect_wall(t_data *img, int pos_x, int pos_y, int scale)
{
	int		i;
	int		j;
	int		color;

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
	int		color;

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
