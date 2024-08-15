/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 10:02:03 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void display(t_data *cub)
{
	double x;
	int side;
	double wallDist;
	
	x = 1;
	side = 0;
	direction_calc(cub, 0);
	while(x <  WIN_W)
	{
		cub->player->cam->cameraX = (2 * x / (double) WIN_W) - 1;
		cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
		cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
		delta_calc_ray(cub);
		step_calc_ray(cub);
		side = side_calc_ray(cub);
		if(side == 1)
			wallDist = fabs((cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX));
		else
			wallDist = fabs((cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY));
		line_display(cub, x, wallDist, side);
		x++;
	}
}

void delta_calc_ray(t_data *cub)
{
	cub->player->cam->r_mapX = (int)cub->player->posX;
	cub->player->cam->r_mapY = (int)cub->player->posY;
	if (cub->player->cam->rayDirX != 0)
		cub->player->cam->r_deltaX = fabs(1 / cub->player->cam->rayDirX); 
	else
		cub->player->cam->r_deltaX = 1e30;
	if (cub->player->cam->rayDirY != 0)
		cub->player->cam->r_deltaY = fabs(1 / cub->player->cam->rayDirY);
	else
		cub->player->cam->r_deltaY = 1e30;
}

void step_calc_ray(t_data *cub)
{
	if (cub->player->cam->rayDirX < 0)
	{
		cub->player->cam->r_stepX = -1;
		cub->player->cam->r_sideDistX = (cub->player->posX - cub->player->cam->r_mapX) * cub->player->cam->r_deltaX;
	}
	else
	{
		cub->player->cam->r_stepX = 1;
		cub->player->cam->r_sideDistX = (cub->player->cam->r_mapX + 1.0 - cub->player->posX) * cub->player->cam->r_deltaX;
	}
	if (cub->player->cam->rayDirY < 0)
	{
		cub->player->cam->r_stepY = -1;
		cub->player->cam->r_sideDistY = (cub->player->posY - cub->player->cam->r_mapY) * cub->player->cam->r_deltaY;
	}
	else
	{
		cub->player->cam->r_stepY = 1;
		cub->player->cam->r_sideDistY = (cub->player->cam->r_mapY + 1.0 - cub->player->posY) * cub->player->cam->r_deltaY;
	}
}

int side_calc_ray(t_data *cub)
{
	int hit;
	int side;

	side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (fabs(cub->player->cam->r_sideDistX) < fabs(cub->player->cam->r_sideDistY))
		{
			cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
			cub->player->cam->r_mapX += cub->player->cam->r_stepX;
			side = 1;
		}
		else
		{
			cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
			cub->player->cam->r_mapY += cub->player->cam->r_stepY;
			side = 0;
		}
		if(cub->player->cam->r_mapX >= 0 && cub->player->cam->r_mapY >= 0)
		{
			if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] > '0')
				hit = 1;
		}
	}
	return (side);
}

int		line_display(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.yStart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yStart < 0)
		line_prop.yStart = 0;
    line_prop.yEnd = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yEnd >= WIN_H)
		line_prop.yEnd = WIN_H - 1;
	line_prop.wallX = wallX_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return(1);
}

int wallX_calculator(t_data *cub, double wallDist, int side)
{
	double wall_pos;
	int wallX;

	if(side == 0)
		wall_pos = (cub->player->posX + (wallDist) * cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + (wallDist) * cub->player->cam->rayDirY;
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
	else
	{
		if (cub->player->cam->rayDirY < 0)
			liner(cub, line_prop, cub->texNorth);
		else
			liner(cub, line_prop, cub->texSouth);	
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
