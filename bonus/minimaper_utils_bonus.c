/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:16:41 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 15:57:24 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void direction_calc(t_data *cub, double ang)
{
	cub->player->pov->dirx = cos(cub->player->p_ang + ang);
	cub->player->pov->diry = sin(cub->player->p_ang + ang);
	if (cub->player->pov->dirx < 0.00001 && cub->player->pov->dirx > -0.00001)
		cub->player->pov->dirx = 0;
	if (cub->player->pov->diry < 0.00001 && cub->player->pov->diry > -0.00001)
		cub->player->pov->diry = 0;	
}

void delta_calc(t_data *cub)
{
	cub->player->pov->mapx = (int)cub->player->posx;
	cub->player->pov->mapy = (int)cub->player->posy;
	if (cub->player->pov->dirx != 0)
		cub->player->pov->deltax = fabs(1 / cub->player->pov->dirx); 
	else
		cub->player->pov->deltax = 1e30;
	if (cub->player->pov->diry != 0)
		cub->player->pov->deltay = fabs(1 / cub->player->pov->diry);
	else
		cub->player->pov->deltay = 1e30;
}

void step_calc(t_data *cub)
{
	if (cub->player->pov->dirx < 0)
	{
		cub->player->pov->stepx = -1;
		cub->player->pov->sidedistx = (cub->player->posx - cub->player->pov->mapx) * cub->player->pov->deltax;
	}
	else
	{
		cub->player->pov->stepx = 1;
		cub->player->pov->sidedistx = (cub->player->pov->mapx + 1.0 - cub->player->posx) * cub->player->pov->deltax;
	}
	if (cub->player->pov->diry < 0)
	{
		cub->player->pov->stepy = -1;
		cub->player->pov->sidedisty = (cub->player->posy - cub->player->pov->mapy) * cub->player->pov->deltay;
	}
	else
	{
		cub->player->pov->stepy = 1;
		cub->player->pov->sidedisty = (cub->player->pov->mapy + 1.0 - cub->player->posy) * cub->player->pov->deltay;
	}
}

int side_calc(t_data *cub)
{
	int hit;
	int side;

	side = 0;
	hit = 0;
	
	if (cub->map[(int)cub->player->posy][(int)cub->player->posx] == 'D')
		hit = distance_doors_within(cub, &side);
	while (hit == 0)
	{
		if (fabs(cub->player->pov->sidedistx) < fabs(cub->player->pov->sidedisty))
		{
			cub->player->pov->sidedistx += cub->player->pov->deltax;
			cub->player->pov->mapx += cub->player->pov->stepx;
			side = 1;
		}
		else
		{
			cub->player->pov->sidedisty += cub->player->pov->deltay;
			cub->player->pov->mapy += cub->player->pov->stepy;
			side = 0;
		}
		if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] > '0')
			hit = distance_doors(cub, &side);
	}
	return (side);
}



int distance_doors(t_data *cub, int *side)
{
	int door_num;
	double mid_distX;
	double mid_distY;

	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == '1')
		return (1);
	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == 'D')
	{
		door_num = search_door(cub, (double)cub->player->pov->mapx, (double)cub->player->pov->mapy);
		if (cub->doors[door_num].open == true)
			return (0);
		if (cub->doors[door_num].orientation == 1)
		{
			if (cub->player->pov->stepx == -1)
				mid_distX = (cub->player->posx - (cub->player->pov->mapx + 0.5)) * cub->player->pov->deltax;
			else
				mid_distX = ((cub->player->pov->mapx + 0.5) - cub->player->posx) * cub->player->pov->deltax;
			if (fabs(mid_distX) < fabs(cub->player->pov->sidedisty))
			{
				cub->player->pov->sidedistx = mid_distX;
				*side = 11;
			}
			else
			{
				cub->player->pov->sidedisty += cub->player->pov->deltay;
				cub->player->pov->mapy += cub->player->pov->stepy;
				*side = 0;
			}
		}
		else if (cub->doors[door_num].orientation == 0)
		{
			if (cub->player->pov->stepy == -1)
				mid_distY = (cub->player->posy - (cub->player->pov->mapy + 0.5)) * cub->player->pov->deltay;
			else
				mid_distY = ((cub->player->pov->mapy + 0.5) - cub->player->posy) * cub->player->pov->deltay;
			if (fabs(mid_distY) < fabs(cub->player->pov->sidedistx))
			{
				cub->player->pov->sidedisty = mid_distY;
				*side = 10;
			}
			else
			{
				cub->player->pov->sidedistx += cub->player->pov->deltax;
				cub->player->pov->mapx += cub->player->pov->stepx;
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
	
	door_num = search_door(cub, cub->player->posx, cub->player->posy);
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
	{
		if (cub->player->pov->stepx == -1)
			mid_dist = (cub->player->posx - (cub->player->pov->mapx + 0.5)) * cub->player->pov->deltax;
		else
			mid_dist = ((cub->player->pov->mapx + 0.5) - cub->player->posx) * cub->player->pov->deltax;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->pov->sidedisty))
		{
			cub->player->pov->sidedistx = mid_dist;
			*side = 11;
		}
		else
		{
			cub->player->pov->sidedisty += cub->player->pov->deltay;
			cub->player->pov->mapy += cub->player->pov->stepy;
			*side = 0;
		}
	}
	else if(cub->doors[door_num].orientation == 0)
	{
		if (cub->player->pov->stepy == -1)
			mid_dist = (cub->player->posy - (cub->player->pov->mapy + 0.5)) * cub->player->pov->deltay;
		else
			mid_dist = ((cub->player->pov->mapy + 0.5) - cub->player->posy) * cub->player->pov->deltay;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->pov->sidedistx))
		{
			cub->player->pov->sidedisty = mid_dist;
			*side = 10;
		}
		else
		{
			cub->player->pov->sidedistx += cub->player->pov->deltax;
			cub->player->pov->mapx += cub->player->pov->stepx;
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