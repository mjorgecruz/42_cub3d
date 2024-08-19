/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:55:44 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 14:28:59 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

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


int		line_display_door(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	int		hitx;
	int		hity;
	int		door_num;
	
	hitx = cub->player->posX + wallDist * cub->player->cam->rayDirX;
	hity = cub->player->posY + wallDist * cub->player->cam->rayDirY;
	door_num = search_door(cub, hitx, hity);
	if (line_to_print(cub, door_num, wallDist) == 0)
		return(1);
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.yStart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yStart < 0)
		line_prop.yStart = 0;
    line_prop.yEnd = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yEnd >= WIN_H)
		line_prop.yEnd = WIN_H - 1;
	line_prop.wallX = wallx_calculator_door(cub, wallDist, side, door_num);
	line_maker(cub, line_prop, side);
	return(1);
}

int		line_display_fire(t_data *cub, int x, double wallDist, int side)
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
