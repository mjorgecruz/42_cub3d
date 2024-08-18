/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:50:49 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 17:57:22 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
			side = smaller_x_step(cub);
		else
			side = smaller_y_step(cub);
		if (cub->player->cam->r_mapX >= 0 && cub->player->cam->r_mapY >= 0)
		{
			if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] \
				== '1')
				hit = 1;
		}
	}
	return (side);
}
int	smaller_x_step(t_data *cub)
{
	cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
	cub->player->cam->r_mapX += cub->player->cam->r_stepX;
	return (1);
}
int	smaller_y_step(t_data *cub)
{
	cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
	cub->player->cam->r_mapY += cub->player->cam->r_stepY;
	return (0);
}

int side_calc_ray_bonus(t_data *cub, int x)
{
	int hit;
	int side;

	side = 0;
	hit = 0;
	if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] == '1')
		return (1);
	if (cub->map[(int)cub->player->posY][(int)cub->player->posX] == 'D')
		hit = distance_doors_within_cam(cub, &side, x);
	while (hit == 0)
	{
		if (fabs(cub->player->cam->r_sideDistX) < fabs(cub->player->cam->r_sideDistY))
			side = smaller_x_step(cub);
		else
			side = smaller_y_step(cub);
		if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] > '0')
			hit = distance_doors_cam(cub, &side, x);
	}
	return (side);
}
