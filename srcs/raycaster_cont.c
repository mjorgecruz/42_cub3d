/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:19:48 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/18 11:27:46 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
				> '0')
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

