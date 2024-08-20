/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:31:58 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/20 16:42:54 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int door_side_calc_x_mini(t_data *cub);
int door_side_calc_y_mini(t_data *cub);
int door_calc_within_x_mini(t_data *cub);
int door_calc_within_y_mini(t_data *cub);

int	distance_doors(t_data *cub, int *side)
{
	int		door_num;

	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == '1')
		return (1);
	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == 'D')
	{
		door_num = search_door(cub, (double)cub->player->pov->mapx, (double)cub->player->pov->mapy);
		if (cub->doors[door_num].open == true)
			return (0);
		if (cub->doors[door_num].orientation == 1)
		{
			*side = door_side_calc_x_mini(cub);
		}
		else if (cub->doors[door_num].orientation == 0)
		{
			*side = door_side_calc_y_mini(cub);
		}
	}
	return 1;
}

int door_side_calc_x_mini(t_data *cub)
{
	double mid_distx;
	int side;
	
	if (cub->player->pov->stepx == -1)
		mid_distx = (cub->player->posx - (cub->player->pov->mapx + 0.5)) * cub->player->pov->deltax;
	else
		mid_distx = ((cub->player->pov->mapx + 0.5) - cub->player->posx) * cub->player->pov->deltax;
	if (fabs(mid_distx) < fabs(cub->player->pov->sidedisty))
	{
		cub->player->pov->sidedistx = mid_distx;
		side = 11;
	}
	else
	{
		cub->player->pov->sidedisty += cub->player->pov->deltay;
		cub->player->pov->mapy += cub->player->pov->stepy;
		side = 0;
	}
	return(side);
}

int door_side_calc_y_mini(t_data *cub)
{
	double mid_disty;
	int side;

	if (cub->player->pov->stepy == -1)
		mid_disty = (cub->player->posy - (cub->player->pov->mapy + 0.5)) * cub->player->pov->deltay;
	else
		mid_disty = ((cub->player->pov->mapy + 0.5) - cub->player->posy) * cub->player->pov->deltay;
	if (fabs(mid_disty) < fabs(cub->player->pov->sidedistx))
	{
		cub->player->pov->sidedisty = mid_disty;
		side = 10;
	}
	else
	{
		cub->player->pov->sidedistx += cub->player->pov->deltax;
		cub->player->pov->mapx += cub->player->pov->stepx;
		side = 1;
	}
	return(side);
}

int	distance_doors_within(t_data *cub, int *side)
{
	int		door_num;
		
	door_num = search_door(cub, cub->player->posx, cub->player->posy);
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
	{
		*side = door_calc_within_x_mini(cub);
	}
	else if(cub->doors[door_num].orientation == 0)
	{
		*side = door_calc_within_y_mini(cub);
	}
	return (1);
}

int door_calc_within_x_mini(t_data *cub)
{
	double mid_dist;
	int side;
	
	if (cub->player->pov->stepx == -1)
		mid_dist = (cub->player->posx - (cub->player->pov->mapx + 0.5)) * cub->player->pov->deltax;
	else
		mid_dist = ((cub->player->pov->mapx + 0.5) - cub->player->posx) * cub->player->pov->deltax;
	if (mid_dist < 0)
		return (0);
	if (fabs(mid_dist) < fabs(cub->player->pov->sidedisty))
	{
		cub->player->pov->sidedistx = mid_dist;
		side = 11;
	}
	else
	{
		cub->player->pov->sidedisty += cub->player->pov->deltay;
		cub->player->pov->mapy += cub->player->pov->stepy;
		side = 0;
	}
	return (side);
}

int door_calc_within_y_mini(t_data *cub)
{
	double mid_dist;
	int side;
	
	if (cub->player->pov->stepy == -1)
		mid_dist = (cub->player->posy - (cub->player->pov->mapy + 0.5)) * cub->player->pov->deltay;
	else
		mid_dist = ((cub->player->pov->mapy + 0.5) - cub->player->posy) * cub->player->pov->deltay;
	if (mid_dist < 0)
		return (0);
	if (fabs(mid_dist) < fabs(cub->player->pov->sidedistx))
	{
		cub->player->pov->sidedisty = mid_dist;
		side = 10;
	}
	else
	{
		cub->player->pov->sidedistx += cub->player->pov->deltax;
		cub->player->pov->mapx += cub->player->pov->stepx;
		side = 1;
	}
	return(side);
}
