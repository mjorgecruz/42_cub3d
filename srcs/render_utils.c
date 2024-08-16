/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:23:23 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 18:56:21 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIN_W && y < WIN_H && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

int	bresenham(t_data *img, double u1, double v1)
{
	double	varu;
	double	varv;
	int		max;
	int		map_scale;
	int		i;

	map_scale = 20;
	img->u = img->player->posX * map_scale;
	img->v = img->player->posY * map_scale;
	u1 = u1 * map_scale;
	v1 = v1 * map_scale;
	varu = u1 - img->u;
	varv = v1 - img->v;
	max = max_finder(varu, varv);
	varu /= max;
	varv /= max;
	i = 0;
	while (((int)(img->u - u1) || (int)(img->v - v1)))
	{
		pixel_put(img, (int)img->u, (int)img->v, 0xFFFFFF);
		img->u += varu;
		img->v += varv;
		i++;
	}
	return (1);
}

int	max_finder(double varu, double varv)
{
	if (varu < 0)
		varu *= (-1);
	if (varv < 0)
		varv *= (-1);
	if (varu < varv)
		return (varv);
	else
		return (varu);
}
