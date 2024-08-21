/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:57:10 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:59:28 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int		line_to_print(t_data *cub, int door_num, double walldist);
int		line_maker(t_data *cub, t_castInfo line_prop, int side);
void	liner(t_data *cub, t_castInfo line_prop, t_img tex);
void	liner_fire(t_data *cub, t_castInfo line_prop, int pos);

int	line_to_print(t_data *cub, int door_num, double walldist)
{
	double	wall_pos;

	if (cub->doors[door_num].orientation == 0)
		wall_pos = (cub->player->posx + (walldist) * cub->player->cam->raydirx);
	else
		wall_pos = cub->player->posy + (walldist) * cub->player->cam->raydiry;
	wall_pos -= (double)((int)wall_pos);
	if (cub->doors[door_num].open == false)
	{
		if (wall_pos > 1.0 - cub->doors[door_num].position * 0.8)
			return (0);
	}
	else if (cub->doors[door_num].open == true)
	{
		if (1 - wall_pos < cub->doors[door_num].position * 0.8)
			return (0);
	}
	return (1);
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
	else if (side == 0)
	{
		if (cub->player->cam->raydiry < 0)
			liner(cub, line_prop, cub->texnorth);
		else
			liner(cub, line_prop, cub->texsouth);
	}
	else if (side == 20)
		liner_fire(cub, line_prop, 0);
	else
		liner(cub, line_prop, cub->door);
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
			line_prop.wallx * (tex.bits_per_pixel / 8))));
		pixel_put(cub, line_prop.x, pos, color);
		pos++;
	}
}

void	liner_fire(t_data *cub, t_castInfo line_prop, int pos)
{
	int		color;
	double	step;
	int		texy;
	double	texpos;
	t_img	tex;

	if (cub->fire_num == 0)
		tex = cub->fire1;
	else if (cub->fire_num == 1)
		tex = cub->fire2;
	else if (cub->fire_num == 2)
		tex = cub->fire3;
	step = 1.0 * tex.height / line_prop.line_height;
	pos = line_prop.ystart - 1;
	texpos = (line_prop.ystart - WIN_H / 2 + line_prop.line_height / 2) * step;
	while (++pos <= line_prop.yend)
	{
		texy = (int)texpos & (tex.height - 1);
		texpos += step;
		color = *((int *)(tex.data + (texy * tex.line_length + \
			line_prop.wallx * (tex.bits_per_pixel / 8))));
		if (color != 0x000000)
			pixel_put(cub, line_prop.x, pos, color);
	}
}
