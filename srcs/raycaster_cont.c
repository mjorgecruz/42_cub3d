/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:19:48 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 18:23:51 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	calculus_side_r(t_data *cub)
{
	cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
	cub->player->cam->r_mapX += cub->player->cam->r_stepX;
	return (1);
}

static int	calc_side_else(t_data *cub)
{
	cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
	cub->player->cam->r_mapY += cub->player->cam->r_stepY;
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
		if (fabs(cub->player->cam->r_sideDistX) < \
			fabs(cub->player->cam->r_sideDistY))
			side = calculus_side_r(cub);
		else
			side = calc_side_else(cub);
		if (cub->player->cam->r_mapX >= 0 && cub->player->cam->r_mapY >= 0)
		{
			if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] \
				> '0')
				hit = 1;
		}
	}
	return (side);
}
