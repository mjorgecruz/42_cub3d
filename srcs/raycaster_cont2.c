/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cont2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:25:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 18:30:34 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	line_display(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo	line_prop;

	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.yStart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
	if (line_prop.yStart < 0)
		line_prop.yStart = 0;
	line_prop.yEnd = (int)(line_prop.line_height / 2 + WIN_H / 2);
	if (line_prop.yEnd >= WIN_H)
		line_prop.yEnd = WIN_H - 1;
	line_prop.wallX = wallX_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return (1);
}

int	wallX_calculator(t_data *cub, double wallDist, int side)
{
	double	wall_pos;
	int		wallX;

	if (side == 0)
		wall_pos = (cub->player->posX + (wallDist) * \
			cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + (wallDist) * \
			cub->player->cam->rayDirY;
	wall_pos -= (double)((int) wall_pos);
	wallX = (int)(wall_pos * (double)(cub->texNorth.width));
	return (wallX);
}

int	line_maker(t_data *cub, t_castInfo line_prop, int side)
{
	if (side == 1)
	{
		if (cub->player->cam->rayDirX > 0)
			liner(cub, line_prop, cub->texEast);
		else
			liner(cub, line_prop, cub->texWest);
	}
	else
	{
		if (cub->player->cam->rayDirY < 0)
			liner(cub, line_prop, cub->texNorth);
		else
			liner(cub, line_prop, cub->texSouth);
	}
	return (1);
}

void	liner(t_data *cub, t_castInfo line_prop, t_img tex)
{
	int		color;
	double	step;
	int		texY;
	int		pos;
	double	texPos;

	step = 1.0 * tex.height / line_prop.line_height;
	pos = line_prop.yStart;
	texPos = (line_prop.yStart - WIN_H / 2 + line_prop.line_height / 2) * step;
	while (pos <= line_prop.yEnd)
	{
		texY = (int)texPos & (tex.height - 1);
		texPos += step;
		color = *((int *)(tex.data + (texY * tex.line_length + \
			line_prop.wallX * (cub->texNorth.bits_per_pixel / 8))));
		pixel_put(cub, line_prop.x, pos, color);
		pos++;
	}
}
