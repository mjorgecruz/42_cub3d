/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:57:10 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 22:07:46 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	line_to_print(t_data *cub, int door_num, double walldist)
{
	double wall_pos;
	
	if(cub->doors[door_num].orientation == 0)
		wall_pos = (cub->player->posX + (walldist) * cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + (walldist) * cub->player->cam->rayDirY;
	wall_pos-=(double)((int) wall_pos);
	if (cub->doors[door_num].open == false)
	{
		if (wall_pos > 1.0 - cub->doors[door_num].position * 0.8)
	 		return (0);
	}
	else if(cub->doors[door_num].open == true)
	{
		if (1 - wall_pos < cub->doors[door_num].position * 0.8)
	 		return (0);	
	}
	return (1);
}

int wallX_calculator(t_data *cub, double wallDist, int side)
{
	double wall_pos;
	int wallX;

	if(side == 0 || side == 10)
		wall_pos = (cub->player->posX + (wallDist) * cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + (wallDist) * cub->player->cam->rayDirY;
	wall_pos-=(double)((int) wall_pos);
	wallX = (int)(wall_pos * (double)(cub->texNorth.width));
	return(wallX);
}

int	wallx_calculator_door(t_data *cub, double wallDist, int side, int door_num)
{
	double wall_pos;
	int wallX;

	if(side == 0 || side == 10)
		wall_pos = (cub->player->posX - cub->doors[door_num].position * 0.8 + (wallDist) * cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + cub->doors[door_num].position * 0.8 + (wallDist) * cub->player->cam->rayDirY;
	wall_pos-=(double)((int) wall_pos);
	wallX = (int)(wall_pos * (double)(cub->texNorth.width));
	return(wallX);
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
	else if (side == 0)
	{
		if (cub->player->cam->rayDirY < 0)
			liner(cub, line_prop, cub->texNorth);
		else
			liner(cub, line_prop, cub->texSouth);	
	}
	else
	{
		liner(cub, line_prop, cub->door);
	}
	return(1);
}

void	liner(t_data *cub, t_castInfo line_prop, t_img tex)
{
	int color;
	double step;
	int texY;
	int pos;
	double texPos;
	
	step = 1.0 * tex.height / line_prop.line_height;
	pos = line_prop.yStart;
	texPos = (line_prop.yStart - WIN_H / 2 + line_prop.line_height / 2) * step;
	while (pos <= line_prop.yEnd)
	{
		texY = (int)texPos & (tex.height - 1);
		texPos += step;
		color = *((int *)(tex.data + (texY * tex.line_length + line_prop.wallX * (cub->texNorth.bits_per_pixel / 8))));
		pixel_put(cub, line_prop.x, pos, color);
		pos++;
	}
}
