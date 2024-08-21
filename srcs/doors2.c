/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:30:35 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:27 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	door_pos_hor_helper(t_data *cub)
{
	cub->player->posy = cub->player->posy + sin(cub->player->p_ang) / 20;
}

int	distance_doors(t_data *cub, int *side)
{
	int		door_num;

	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == '1')
		return (1);
	if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] == 'D')
	{
		door_num = search_door(cub, (double)cub->player->pov->mapx, \
			(double)cub->player->pov->mapy);
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
	return (1);
}

int	distance_doors_within(t_data *cub, int *side)
{
	int	door_num;

	door_num = search_door(cub, cub->player->posx, cub->player->posy);
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
	{
		*side = door_calc_within_x_mini(cub);
	}
	else if (cub->doors[door_num].orientation == 0)
	{
		*side = door_calc_within_y_mini(cub);
	}
	return (1);
}

void	door_neg_ver_helper(t_data *cub)
{
	cub->player->posx = cub->player->posx - cos(cub->player->p_ang) / 20;
}

void	door_math_helper(t_data *cub)
{
	cub->player->posy = cub->player->posy - sin(cub->player->p_ang) / 20;
}
