/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 15:00:43 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

void display_bonus(t_data *cub)
{
	double x;
	
	x =  1;
	direction_calc(cub, 0);
	while(x <  WIN_W)
	{
		camera_calculations(cub, x);
		wall_displayer(cub, x);
		x++;
	}
	x = 1;
	while(x <  WIN_W)
	{
		camera_calculations(cub, x);
		sprite_displayer(cub, x);
		x++;
	}
}

void	camera_calculations(t_data *cub, int x)
{
	cub->player->cam->cameraX = (2 * x / (double) WIN_W) - 1;
	cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
	cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
	delta_calc_ray(cub);
	step_calc_ray(cub);	
}

void	wall_displayer(t_data *cub, int x)
{
	int side;
	double walldist;
	
	walldist = 0.0;
	side = side_calc_ray(cub);
	if(side == 1)
		walldist = fabs((cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX));
	else if (side == 0)
		walldist = fabs((cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY));
	if (walldist < 0.0001)
		walldist = 0.0001;
	if (side == 0 || side == 1)
		line_display(cub, x, walldist, side);
}

void	sprite_displayer(t_data *cub, int x)
{
	int side;
	double walldist;
	
	walldist = 0.0;
	side = side_calc_ray_bonus(cub, x);
	if (side == 10)
		walldist = fabs((cub->player->cam->r_sideDistY));
	else if (side == 11)
		walldist = fabs((cub->player->cam->r_sideDistX));
	else if(side == 21)
		walldist = fabs((cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX));
	else if (side == 20)
		walldist = fabs((cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY));
	if (walldist < 0.0001)
		walldist = 0.0001;
	if (side == 10 || side == 11)
		line_display_door(cub, x, walldist, side);
	else if (side == 20 || side == 21)
		line_display_fire(cub, x, walldist, side);
}
