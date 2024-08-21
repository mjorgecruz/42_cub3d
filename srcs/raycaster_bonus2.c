/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:50:49 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:59:35 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	side_calc_ray(t_data *cub);
int	smaller_x_step(t_data *cub);
int	smaller_y_step(t_data *cub);
int	side_calc_ray_bonus(t_data *cub, int x);

int	side_calc_ray(t_data *cub)
{
	int	hit;
	int	side;

	side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (fabs(cub->player->cam->r_sidedistx) < \
			fabs(cub->player->cam->r_sidedisty))
			side = smaller_x_step(cub);
		else
			side = smaller_y_step(cub);
		if (cub->player->cam->r_mapx >= 0 && cub->player->cam->r_mapy >= 0)
		{
			if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] \
				== '1')
				hit = 1;
		}
	}
	return (side);
}

int	smaller_x_step(t_data *cub)
{
	cub->player->cam->r_sidedistx += cub->player->cam->r_deltax;
	cub->player->cam->r_mapx += cub->player->cam->r_stepx;
	return (1);
}

int	smaller_y_step(t_data *cub)
{
	cub->player->cam->r_sidedisty += cub->player->cam->r_deltay;
	cub->player->cam->r_mapy += cub->player->cam->r_stepy;
	return (0);
}

int	side_calc_ray_bonus(t_data *cub, int x)
{
	int	hit;
	int	side;

	side = 0;
	hit = 0;
	if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] == '1')
		return (1);
	if (cub->map[(int)cub->player->posy][(int)cub->player->posx] == 'D')
		hit = distance_doors_within_cam(cub, &side, x);
	while (hit == 0)
	{
		if (fabs(cub->player->cam->r_sidedistx) < \
			fabs(cub->player->cam->r_sidedisty))
			side = smaller_x_step(cub);
		else
			side = smaller_y_step(cub);
		if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] > '0')
			hit = distance_sprites_cam(cub, &side, x);
	}
	return (side);
}
