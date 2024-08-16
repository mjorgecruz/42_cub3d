/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 18:45:46 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculus_display(t_data *cub, double x)
{
	cub->player->cam->cameraX = (2 * x / (double) WIN_W) - 1;
	cub->player->cam->rayDirX = cub->player->pov->dirX + \
		cub->player->cam->planeX * cub->player->cam->cameraX;
	cub->player->cam->rayDirY = cub->player->pov->dirY + \
		cub->player->cam->planeY * cub->player->cam->cameraX;
	delta_calc_ray(cub);
	step_calc_ray(cub);
}

void	display(t_data *cub)
{
	double	x;
	int		side;
	double	wallDist;

	x = 1;
	side = 0;
	direction_calc(cub, 0);
	while (x < WIN_W)
	{
		calculus_display(cub, x);
		side = side_calc_ray(cub);
		if (side == 1)
			wallDist = fabs((cub->player->cam->r_sideDistX - \
				cub->player->cam->r_deltaX));
		else
			wallDist = fabs((cub->player->cam->r_sideDistY - \
				cub->player->cam->r_deltaY));
		if (wallDist < 0.0001)
			wallDist = 0.0001;
		line_display(cub, x, wallDist, side);
		x++;
	}
}

void	delta_calc_ray(t_data *cub)
{
	cub->player->cam->r_mapX = (int)cub->player->posX;
	cub->player->cam->r_mapY = (int)cub->player->posY;
	if (cub->player->cam->rayDirX != 0)
		cub->player->cam->r_deltaX = fabs(1 / cub->player->cam->rayDirX);
	else
		cub->player->cam->r_deltaX = 1e30;
	if (cub->player->cam->rayDirY != 0)
		cub->player->cam->r_deltaY = fabs(1 / cub->player->cam->rayDirY);
	else
		cub->player->cam->r_deltaY = 1e30;
}

void	step_calc_ray(t_data *cub)
{
	if (cub->player->cam->rayDirX < 0)
	{
		cub->player->cam->r_stepX = -1;
		cub->player->cam->r_sideDistX = (cub->player->posX - \
			cub->player->cam->r_mapX) * cub->player->cam->r_deltaX;
	}
	else
	{
		cub->player->cam->r_stepX = 1;
		cub->player->cam->r_sideDistX = (cub->player->cam->r_mapX + 1.0 - \
			cub->player->posX) * cub->player->cam->r_deltaX;
	}
	if (cub->player->cam->rayDirY < 0)
	{
		cub->player->cam->r_stepY = -1;
		cub->player->cam->r_sideDistY = (cub->player->posY - \
			cub->player->cam->r_mapY) * cub->player->cam->r_deltaY;
	}
	else
	{
		cub->player->cam->r_stepY = 1;
		cub->player->cam->r_sideDistY = (cub->player->cam->r_mapY + 1.0 - \
			cub->player->posY) * cub->player->cam->r_deltaY;
	}
}
