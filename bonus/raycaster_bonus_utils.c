/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:55:44 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 15:59:11 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void delta_calc_ray(t_data *cub)
{
	cub->player->cam->r_mapx = (int)cub->player->posx;
	cub->player->cam->r_mapy = (int)cub->player->posy;
	if (cub->player->cam->raydirx != 0)
		cub->player->cam->r_deltax = fabs(1 / cub->player->cam->raydirx); 
	else
		cub->player->cam->r_deltax = 1e30;
	if (cub->player->cam->raydiry != 0)
		cub->player->cam->r_deltay = fabs(1 / cub->player->cam->raydiry);
	else
		cub->player->cam->r_deltay = 1e30;
}

void step_calc_ray(t_data *cub)
{
	if (cub->player->cam->raydirx < 0)
	{
		cub->player->cam->r_stepx = -1;
		cub->player->cam->r_sidedistx = (cub->player->posx - cub->player->cam->r_mapx) * cub->player->cam->r_deltax;
	}
	else
	{
		cub->player->cam->r_stepx = 1;
		cub->player->cam->r_sidedistx = (cub->player->cam->r_mapx + 1.0 - cub->player->posx) * cub->player->cam->r_deltax;
	}
	if (cub->player->cam->raydiry < 0)
	{
		cub->player->cam->r_stepy = -1;
		cub->player->cam->r_sidedisty = (cub->player->posy - cub->player->cam->r_mapy) * cub->player->cam->r_deltay;
	}
	else
	{
		cub->player->cam->r_stepy = 1;
		cub->player->cam->r_sidedisty = (cub->player->cam->r_mapy + 1.0 - cub->player->posy) * cub->player->cam->r_deltay;
	}
}


int		line_display(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.ystart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.ystart < 0)
		line_prop.ystart = 0;
    line_prop.yend = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yend >= WIN_H)
		line_prop.yend = WIN_H - 1;
	line_prop.wallx = wallX_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return(1);
}


int		line_display_door(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	int		hitx;
	int		hity;
	int		door_num;
	
	hitx = cub->player->posx + wallDist * cub->player->cam->raydirx;
	hity = cub->player->posy + wallDist * cub->player->cam->raydiry;
	door_num = search_door(cub, hitx, hity);
	if (line_to_print(cub, door_num, wallDist) == 0)
		return(1);
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.ystart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.ystart < 0)
		line_prop.ystart = 0;
    line_prop.yend = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yend >= WIN_H)
		line_prop.yend = WIN_H - 1;
	line_prop.wallx = wallx_calculator_door(cub, wallDist, side, door_num);
	line_maker(cub, line_prop, side);
	return(1);
}

int		line_display_fire(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.ystart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.ystart < 0)
		line_prop.ystart = 0;
    line_prop.yend = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yend >= WIN_H)
		line_prop.yend = WIN_H - 1;
	line_prop.wallx = wallX_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return(1);
}
