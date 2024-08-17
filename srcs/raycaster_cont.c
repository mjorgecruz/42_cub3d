/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:19:48 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/17 10:25:34 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	calculus_side_r(t_data *cub)
{
	cub->player->cam->r_sidedistx += cub->player->cam->r_deltax;
	cub->player->cam->r_mapx += cub->player->cam->r_stepx;
	return (1);
}

static int	calc_side_else(t_data *cub)
{
	cub->player->cam->r_sidedisty += cub->player->cam->r_deltay;
	cub->player->cam->r_mapy += cub->player->cam->r_stepy;
	return (0);
}

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
			side = calculus_side_r(cub);
		else
			side = calc_side_else(cub);
		if (cub->player->cam->r_mapx >= 0 && cub->player->cam->r_mapy >= 0)
		{
			if (cub->map[cub->player->cam->r_mapy][cub->player->cam->r_mapx] \
				> '0')
				hit = 1;
		}
	}
	return (side);
}
