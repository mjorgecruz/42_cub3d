/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:56 by masoares          #+#    #+#             */
/*   Updated: 2024/08/24 16:36:56 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			distance_sprites_cam(t_data *cub, int *side, int x);
int			raycaster_recursive(t_data *cub, int x);
t_closest	temp_var_holder(t_data *cub);
int			door_side_calc_x(t_data *cub);
int			door_side_calc_y(t_data *cub);

int	distance_sprites_cam(t_data *cub, int *side, int x)
{
	int	num;

	if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] == '1')
		return (1);
	if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] == 'D')
	{
		*side = raycaster_recursive(cub, x);
		num = search_door(cub, (double)cub->player->cam->r_mapx, \
			(double)cub->player->cam->r_mapy);
		if (cub->doors[num].orientation == 1)
			*side = door_side_calc_x(cub);
		else if (cub->doors[num].orientation == 0)
			*side = door_side_calc_y(cub);
	}
	if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] == 'F')
	{
		*side = raycaster_recursive(cub, x);
		num = search_fire(cub, (double)cub->player->cam->r_mapx, \
			(double)cub->player->cam->r_mapy);
		if (cub->fires[num].drawn == 0)
			*side = fire_calc(cub, num);
		else
			*side = 99;
	}
	return (1);
}

int	raycaster_recursive(t_data *cub, int x)
{
	t_closest	door;
	int			side;

	door = temp_var_holder(cub);
	if (fabs(cub->player->cam->r_sidedistx) < \
		fabs(cub->player->cam->r_sidedisty))
	{
		cub->player->cam->r_sidedistx += cub->player->cam->r_deltax;
		cub->player->cam->r_mapx += cub->player->cam->r_stepx;
		side = 1;
	}
	else
	{
		cub->player->cam->r_sidedisty += cub->player->cam->r_deltay;
		cub->player->cam->r_mapy += cub->player->cam->r_stepy;
		side = 0;
	}
	sprite_displayer(cub, x);
	cub->player->cam->r_mapx = door.mapx;
	cub->player->cam->r_mapy = door.mapy;
	cub->player->cam->r_sidedistx = door.sidedistx;
	cub->player->cam->r_sidedisty = door.sidedisty;
	return (side);
}

t_closest	temp_var_holder(t_data *cub)
{
	t_closest	door;

	door.mapx = cub->player->cam->r_mapx;
	door.mapy = cub->player->cam->r_mapy;
	door.sidedistx = cub->player->cam->r_sidedistx;
	door.sidedisty = cub->player->cam->r_sidedisty;
	return (door);
}

int	door_side_calc_x(t_data *cub)
{
	double	mid_distx;
	int		side;

	if (cub->player->cam->r_stepx == -1)
		mid_distx = (cub->player->posx - (cub->player->cam->r_mapx + 0.5)) * \
			cub->player->cam->r_deltax;
	else
		mid_distx = ((cub->player->cam->r_mapx + 0.5) - \
			cub->player->posx) * cub->player->cam->r_deltax;
	if (fabs(mid_distx) < fabs(cub->player->cam->r_sidedisty))
	{
		cub->player->cam->r_sidedistx = mid_distx;
		side = 11;
	}
	else
		side = 0;
	return (side);
}

int	door_side_calc_y(t_data *cub)
{
	double	mid_disty;
	int		side;

	if (cub->player->cam->r_stepy == -1)
		mid_disty = (cub->player->posy - (cub->player->cam->r_mapy + 0.5)) * \
			cub->player->cam->r_deltay;
	else
		mid_disty = ((cub->player->cam->r_mapy + 0.5) - cub->player->posy) * \
			cub->player->cam->r_deltay;
	if (fabs(mid_disty) < fabs(cub->player->cam->r_sidedistx))
	{
		cub->player->cam->r_sidedisty = mid_disty;
		side = 10;
	}
	else
		side = 1;
	return (side);
}
