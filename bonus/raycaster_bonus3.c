/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:56 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 20:01:37 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int distance_doors_cam(t_data *cub, int *side, int x)
{
	int door_num;

	if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] == '1')
		return (1);
	if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] == 'D')
	{
		*side = raycaster_recursive(cub, x);	
		door_num = search_door(cub, (double)cub->player->cam->r_mapX, (double)cub->player->cam->r_mapY);
		if (cub->doors[door_num].orientation == 1)
			*side = door_side_calc_x(cub);
		else if (cub->doors[door_num].orientation == 0)
			*side = door_side_calc_y(cub);
	}
	return 1;
}

//recursive to draw first objects that are further away
int	raycaster_recursive(t_data *cub, int x)
{
	t_closest door;
	int side;

	door = temp_var_holder(cub);
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
	door_displayer(cub, x);
	cub->player->cam->r_mapX = door.mapx;
	cub->player->cam->r_mapY = door.mapy;
	cub->player->cam->r_sideDistX = door.sidedistx;
	cub->player->cam->r_sideDistY = door.sidedisty;	
	return(side);
}

t_closest	temp_var_holder(t_data *cub)
{
	t_closest door;
	
	door.mapx = cub->player->cam->r_mapX;
	door.mapy = cub->player->cam->r_mapY;
	door.sidedistx = cub->player->cam->r_sideDistX;
	door.sidedisty = cub->player->cam->r_sideDistY;
	return(door);
}

int door_side_calc_x(t_data *cub)
{
	double mid_distx;
	int side;
	
	if (cub->player->cam->r_stepX == -1)
		mid_distx = (cub->player->posX - (cub->player->cam->r_mapX + 0.5)) * cub->player->cam->r_deltaX;
	else
		mid_distx = ((cub->player->cam->r_mapX + 0.5) - cub->player->posX) * cub->player->cam->r_deltaX;
	if (fabs(mid_distx) < fabs(cub->player->cam->r_sideDistY))
	{
		cub->player->cam->r_sideDistX = mid_distx;
		side = 11;
	}
	else
		side = 0;
	return (side);
}

int door_side_calc_y(t_data *cub)
{
	double mid_disty;
	int side;

	if (cub->player->cam->r_stepY == -1)
		mid_disty = (cub->player->posY - (cub->player->cam->r_mapY + 0.5)) * cub->player->cam->r_deltaY;
	else
		mid_disty = ((cub->player->cam->r_mapY + 0.5) - cub->player->posY) * cub->player->cam->r_deltaY;
	if (fabs(mid_disty) < fabs(cub->player->cam->r_sideDistX))
	{
		cub->player->cam->r_sideDistY = mid_disty;
		side = 10;
	}
	else
		side = 1;
	return (side);
}