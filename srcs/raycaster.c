/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/10 11:04:57 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void display(t_data *cub)
{
	double x;
	int side;
	double wallDist;
	
	x = 1;
	side = 0;
	direction_calc(cub, 0);
	while(x < WIN_W)
	{
		cub->player->cam->cameraX = (2 * x / WIN_W) - 1;
		cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
		cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
		delta_calc_ray(cub);
		step_calc_ray(cub);
		side = side_calc_ray(cub);
		if(side == 0) 
			wallDist = fabs(cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX);
		else
			wallDist = fabs(cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY);
		
		printf("planeX %f planeY %f wallDist %f\n", cub->player->cam->planeX, cub->player->cam->planeY, wallDist);
		line_display(cub, x, wallDist, side);
		x++;
	}
	printf("\n");
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
		cub->player->cam->r_deltaY = fabs(1 / cub->player->cam->rayDirX);
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
		if (cub->map[cub->player->cam->r_mapX][cub->player->cam->r_mapY] > 0)
			hit = 1;
	}
	return (side);
}

int		line_display(t_data *cub, int x, double wallDist, int side)
{
	//max_height = WIN_H when wallDist = 1
	int line_height;
	int yStart;
	int yEnd;
	int color;
	int pos;
	
	pos = 0;
	line_height = WIN_H / wallDist;
	yStart = (int)(-line_height / 2 + WIN_H / 2);
    if(yStart < 0)
		yStart = 0;
    yEnd = (int)(line_height / 2 + WIN_H / 2);
    if(yEnd >= WIN_H)
		yEnd = WIN_H - 1;
	color = 0xFF0000;
	if (side == 1)
		color = color / 2;
	pos = yStart;
	while (pos <= yEnd)
	{
		pixel_put(cub, x, pos, color);
		pos++;
	}
	return(1);
}
