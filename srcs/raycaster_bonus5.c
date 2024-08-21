/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:54:21 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/20 16:31:05 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	fire_calc(t_data *cub, int num);
int	wallx_calculator(t_data *cub, double walldist, int side);
int	wallx_calculator_door(t_data *cub, double walldist, int side, int door_num);

int	fire_calc(t_data *cub, int num)
{
	double	perp_dist_x;
	double	perp_dist_y;
	double	perpendicular_distance;

	perp_dist_x = (cub->fires[num].pos_x - cub->player->posx) * \
		cub->player->pov->dirx;
	perp_dist_y = (cub->fires[num].pos_y - cub->player->posy) * \
		cub->player->pov->diry;
	perpendicular_distance = perp_dist_x + perp_dist_y;
	cub->player->cam->r_sidedisty = fabs(perpendicular_distance);
	return (20);
}

int	wallx_calculator(t_data *cub, double walldist, int side)
{
	double	wall_pos;
	int		wallx;

	if (side == 0 || side == 10)
		wall_pos = (cub->player->posx + (walldist) * cub->player->cam->raydirx);
	else
		wall_pos = cub->player->posy + (walldist) * cub->player->cam->raydiry;
	wall_pos -= (double)((int)wall_pos);
	if (side == 1)
	{
		if (cub->player->cam->raydirx > 0)
			wallx = (int)(wall_pos * (double)(cub->texeast.width));
		else
			wallx = (int)(wall_pos * (double)(cub->texwest.width));
	}
	else
	{
		if (cub->player->cam->raydiry < 0)
			wallx = (int)(wall_pos * (double)(cub->texnorth.width));
		else
			wallx = (int)(wall_pos * (double)(cub->texsouth.width));
	}
	return (wallx);
}

int	wallx_calculator_door(t_data *cub, double walldist, int side, int door_num)
{
	double	wall_pos;
	int		wallx;

	if (side == 0 || side == 10)
		wall_pos = (cub->player->posx + cub->doors[door_num].position * 0.8 + \
			(walldist) * cub->player->cam->raydirx);
	else
		wall_pos = cub->player->posy + cub->doors[door_num].position * 0.8 + \
			(walldist) * cub->player->cam->raydiry;
	wall_pos -= (double)((int) wall_pos);
	wallx = (int)(wall_pos * (double)(cub->texnorth.width));
	return (wallx);
}
