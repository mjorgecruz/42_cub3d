/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cont2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:25:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/17 11:12:24 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		line_display(t_data *cub, int x, double wallDist, int side);
int		wallx_calculator(t_data *cub, double wallDist, int side);
int		line_maker(t_data *cub, t_castInfo line_prop, int side);
void	liner(t_data *cub, t_castInfo line_prop, t_img tex);

int	line_display(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo	line_prop;

	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.ystart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
	if (line_prop.ystart < 0)
		line_prop.ystart = 0;
	line_prop.yend = (int)(line_prop.line_height / 2 + WIN_H / 2);
	if (line_prop.yend >= WIN_H)
		line_prop.yend = WIN_H - 1;
	line_prop.wallx = wallx_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return (1);
}

int	wallx_calculator(t_data *cub, double wallDist, int side)
{
	double	wall_pos;
	int		wallx;

	if (side == 0)
		wall_pos = (cub->player->posx + (wallDist) * \
			cub->player->cam->raydirx);
	else
		wall_pos = cub->player->posy + (wallDist) * \
			cub->player->cam->raydiry;
	wall_pos -= (double)((int) wall_pos);
	wallx = (int)(wall_pos * (double)(cub->texnorth.width));
	return (wallx);
}

int	line_maker(t_data *cub, t_castInfo line_prop, int side)
{
	if (side == 1)
	{
		if (cub->player->cam->raydirx > 0)
			liner(cub, line_prop, cub->texeast);
		else
			liner(cub, line_prop, cub->texwest);
	}
	else
	{
		if (cub->player->cam->raydiry < 0)
			liner(cub, line_prop, cub->texnorth);
		else
			liner(cub, line_prop, cub->texsouth);
	}
	return (1);
}

void	liner(t_data *cub, t_castInfo line_prop, t_img tex)
{
	int		color;
	double	step;
	int		texy;
	int		pos;
	double	texpos;

	step = 1.0 * tex.height / line_prop.line_height;
	pos = line_prop.ystart;
	texpos = (line_prop.ystart - WIN_H / 2 + line_prop.line_height / 2) * step;
	while (pos <= line_prop.yend)
	{
		texy = (int)texpos & (tex.height - 1);
		texpos += step;
		color = *((int *)(tex.data + (texy * tex.line_length + \
			line_prop.wallx * (cub->texnorth.bits_per_pixel / 8))));
		pixel_put(cub, line_prop.x, pos, color);
		pos++;
	}
}
