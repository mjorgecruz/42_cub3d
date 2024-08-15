/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 10:03:02 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int minimaper(t_data *cub)
{
	int		map_scale;

	map_scale = 20;
	map_drawing(cub, map_scale);
	render_point_player(cub, (int) (cub->player->posX * map_scale), (int) (cub->player->posY * map_scale));
	render_direction(cub);
	return (1);

}

void 	map_drawing(t_data *cub, int map_scale)
{
	double		x;
	double		y;
	
	y = 0;
	x = 0;
	ft_printf("map_w %i  map_h %i", cub->map_w, cub->map_h);
	while (y < cub->map_h && y * map_scale < WIN_H)
	{
		x = 0;
		while (x < cub->map_w && x * map_scale < WIN_W)
		{
			if (cub->map[(int) y][(int) x] == '1')
				render_rect_wall(cub, x, y, map_scale);
			else if (cub->map[(int) y][(int) x] == '0')
				render_rect_ground(cub, x, y, map_scale);
			else
			{
				render_rect_ground(cub, x, y, map_scale);
			}
			x++;
		}
		y++;
	}
}

void render_direction(t_data *cub)
{
	double ang;
	int side; 
	 
	ang = (-cub->player->fov / 2);
	while (ang <= cub->player->fov / 2)
	{
		direction_calc(cub, ang);
		delta_calc(cub);
		step_calc(cub);
		side = side_calc(cub);
		if (side == 1)
			hit_point_vertical(cub);
		else
			hit_point_horizontal(cub);
		bresenham(cub, cub->player->pov->hitX, cub->player->pov->hitY);
		ang+=0.05;
	}
}

void hit_point_vertical(t_data *cub)
{
	if (cub->player->pov->stepX == -1)
	{
		cub->player->pov->hitX = cub->player->pov->mapX + 1;
		cub->player->pov->hitY = cub->player->posY + (cub->player->pov->sideDistX - cub->player->pov->deltaX) * cub->player->pov->dirY;
	}
	else
	{
		cub->player->pov->hitX = cub->player->pov->mapX;
		cub->player->pov->hitY = cub->player->posY + (cub->player->pov->sideDistX - cub->player->pov->deltaX) * cub->player->pov->dirY;
	}
}

void hit_point_horizontal(t_data *cub)
{
	if (cub->player->pov->stepY == -1)
	{
		cub->player->pov->hitX = cub->player->posX + (cub->player->pov->sideDistY - cub->player->pov->deltaY) * cub->player->pov->dirX;
		cub->player->pov->hitY = cub->player->pov->mapY + 1;
	}
	else
	{
		cub->player->pov->hitX = cub->player->posX + (cub->player->pov->sideDistY - cub->player->pov->deltaY) * cub->player->pov->dirX;
		cub->player->pov->hitY = cub->player->pov->mapY;
	}
}
