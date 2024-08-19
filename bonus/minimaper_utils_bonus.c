/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:16:41 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 13:51:54 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

void direction_calc(t_data *cub, double ang)
{
	cub->player->pov->dirX = cos(cub->player->p_ang + ang);
	cub->player->pov->dirY = sin(cub->player->p_ang + ang);
	if (cub->player->pov->dirX < 0.00001 && cub->player->pov->dirX > -0.00001)
		cub->player->pov->dirX = 0;
	if (cub->player->pov->dirY < 0.00001 && cub->player->pov->dirY > -0.00001)
		cub->player->pov->dirY = 0;	
}

void delta_calc(t_data *cub)
{
	cub->player->pov->mapX = (int)cub->player->posX;
	cub->player->pov->mapY = (int)cub->player->posY;
	if (cub->player->pov->dirX != 0)
		cub->player->pov->deltaX = fabs(1 / cub->player->pov->dirX); 
	else
		cub->player->pov->deltaX = 1e30;
	if (cub->player->pov->dirY != 0)
		cub->player->pov->deltaY = fabs(1 / cub->player->pov->dirY);
	else
		cub->player->pov->deltaY = 1e30;
}

void step_calc(t_data *cub)
{
	if (cub->player->pov->dirX < 0)
	{
		cub->player->pov->stepX = -1;
		cub->player->pov->sideDistX = (cub->player->posX - cub->player->pov->mapX) * cub->player->pov->deltaX;
	}
	else
	{
		cub->player->pov->stepX = 1;
		cub->player->pov->sideDistX = (cub->player->pov->mapX + 1.0 - cub->player->posX) * cub->player->pov->deltaX;
	}
	if (cub->player->pov->dirY < 0)
	{
		cub->player->pov->stepY = -1;
		cub->player->pov->sideDistY = (cub->player->posY - cub->player->pov->mapY) * cub->player->pov->deltaY;
	}
	else
	{
		cub->player->pov->stepY = 1;
		cub->player->pov->sideDistY = (cub->player->pov->mapY + 1.0 - cub->player->posY) * cub->player->pov->deltaY;
	}
}

int side_calc(t_data *cub)
{
	int hit;
	int side;

	side = 0;
	hit = 0;
	
	if (cub->map[(int)cub->player->posY][(int)cub->player->posX] == 'D')
		hit = distance_doors_within(cub, &side);
	while (hit == 0)
	{
		if (fabs(cub->player->pov->sideDistX) < fabs(cub->player->pov->sideDistY))
		{
			cub->player->pov->sideDistX += cub->player->pov->deltaX;
			cub->player->pov->mapX += cub->player->pov->stepX;
			side = 1;
		}
		else
		{
			cub->player->pov->sideDistY += cub->player->pov->deltaY;
			cub->player->pov->mapY += cub->player->pov->stepY;
			side = 0;
		}
		if (cub->map[cub->player->pov->mapY][cub->player->pov->mapX] > '0')
			hit = distance_doors(cub, &side);
	}
	return (side);
}



int distance_doors(t_data *cub, int *side)
{
	int door_num;
	double mid_distX;
	double mid_distY;

	if (cub->map[cub->player->pov->mapY][cub->player->pov->mapX] == '1')
		return (1);
	if (cub->map[cub->player->pov->mapY][cub->player->pov->mapX] == 'D')
	{
		door_num = search_door(cub, (double)cub->player->pov->mapX, (double)cub->player->pov->mapY);
		if (cub->doors[door_num].open == true)
			return (0);
		if (cub->doors[door_num].orientation == 1)
		{
			if (cub->player->pov->stepX == -1)
				mid_distX = (cub->player->posX - (cub->player->pov->mapX + 0.5)) * cub->player->pov->deltaX;
			else
				mid_distX = ((cub->player->pov->mapX + 0.5) - cub->player->posX) * cub->player->pov->deltaX;
			if (fabs(mid_distX) < fabs(cub->player->pov->sideDistY))
			{
				cub->player->pov->sideDistX = mid_distX;
				*side = 11;
			}
			else
			{
				cub->player->pov->sideDistY += cub->player->pov->deltaY;
				cub->player->pov->mapY += cub->player->pov->stepY;
				*side = 0;
			}
		}
		else if (cub->doors[door_num].orientation == 0)
		{
			if (cub->player->pov->stepY == -1)
				mid_distY = (cub->player->posY - (cub->player->pov->mapY + 0.5)) * cub->player->pov->deltaY;
			else
				mid_distY = ((cub->player->pov->mapY + 0.5) - cub->player->posY) * cub->player->pov->deltaY;
			if (fabs(mid_distY) < fabs(cub->player->pov->sideDistX))
			{
				cub->player->pov->sideDistY = mid_distY;
				*side = 10;
			}
			else
			{
				cub->player->pov->sideDistX += cub->player->pov->deltaX;
				cub->player->pov->mapX += cub->player->pov->stepX;
				*side = 1;
			}
		}
	}
	return 1;
}

int distance_doors_within(t_data *cub, int *side)
{
	int		door_num;
	double mid_dist;
	
	door_num = search_door(cub, cub->player->posX, cub->player->posY);
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
	{
		if (cub->player->pov->stepX == -1)
			mid_dist = (cub->player->posX - (cub->player->pov->mapX + 0.5)) * cub->player->pov->deltaX;
		else
			mid_dist = ((cub->player->pov->mapX + 0.5) - cub->player->posX) * cub->player->pov->deltaX;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->pov->sideDistY))
		{
			cub->player->pov->sideDistX = mid_dist;
			*side = 11;
		}
		else
		{
			cub->player->pov->sideDistY += cub->player->pov->deltaY;
			cub->player->pov->mapY += cub->player->pov->stepY;
			*side = 0;
		}
	}
	else if(cub->doors[door_num].orientation == 0)
	{
		if (cub->player->pov->stepY == -1)
			mid_dist = (cub->player->posY - (cub->player->pov->mapY + 0.5)) * cub->player->pov->deltaY;
		else
			mid_dist = ((cub->player->pov->mapY + 0.5) - cub->player->posY) * cub->player->pov->deltaY;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->pov->sideDistX))
		{
			cub->player->pov->sideDistY = mid_dist;
			*side = 10;
		}
		else
		{
			cub->player->pov->sideDistX += cub->player->pov->deltaX;
			cub->player->pov->mapX += cub->player->pov->stepX;
			*side = 1;
		}
	}
	return (1);
}

int		search_door(t_data *cub, double x, double y)
{
	int i;

	i = 0;
	while (cub->doors[i].orientation != -1)
	{
		if ((int)cub->doors[i].pos_x == (int) x)
		{
			if  ((int)cub->doors[i].pos_y == (int) y)
				return (i);
		}
		i++;
	}
	return (-1);
}

int		search_fire(t_data *cub, double x, double y)
{
	int i;

	i = 0;
	while (cub->fires[i].pos_x != -1)
	{
		if ((int)cub->fires[i].pos_x == (int) x)
		{
			if  ((int)cub->fires[i].pos_y == (int) y)
				return (i);
		}
		i++;
	}
	return (-1);
}