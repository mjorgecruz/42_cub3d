/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 04:02:09 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void display_bonus(t_data *cub)
{
	double x;
	int side;
	double wallDist;
	int		door_num;
	
	door_num = 0;
	x =  1;
	side = 0;
	if (cub->doors)
	{
		while (cub->doors[door_num].orientation >= 0)
			update_door_position(&(cub->doors[door_num++]));
	}
	direction_calc(cub, 0);
	while(x <  WIN_W)
	{
		cub->player->cam->cameraX = (2 * x / (double) WIN_W) - 1;
		cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
		cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
		delta_calc_ray(cub);
		step_calc_ray(cub);
		side = side_calc_ray(cub);
		if(side == 1)
			wallDist = fabs((cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX));
		else if (side == 0)
			wallDist = fabs((cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY));
		else if (side == 10)
			wallDist = fabs((cub->player->cam->r_sideDistY));
		else if (side == 11)
			wallDist = fabs((cub->player->cam->r_sideDistX));
		if (wallDist < 0.0001)
			wallDist = 0.0001;
		if (side == 0 || side == 1)
			line_display(cub, x, wallDist, side);
		x++;
	}
	x = 1;
	while(x <  WIN_W)
	{
		cub->player->cam->cameraX = (2 * x / (double) WIN_W) - 1;
		cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
		cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
		delta_calc_ray(cub);
		step_calc_ray(cub);
		side = side_calc_ray_bonus(cub);
		if(side == 1)
			wallDist = fabs((cub->player->cam->r_sideDistX  - cub->player->cam->r_deltaX));
		else if (side == 0)
			wallDist = fabs((cub->player->cam->r_sideDistY - cub->player->cam->r_deltaY));
		else if (side == 10)
			wallDist = fabs((cub->player->cam->r_sideDistY));
		else if (side == 11)
			wallDist = fabs((cub->player->cam->r_sideDistX));
		if (wallDist < 0.0001)
			wallDist = 0.0001;
		if (side == 10 || side == 11)
			line_display(cub, x, wallDist, side);
		x++;
	}
}

void delta_calc_ray(t_data *cub)
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

void step_calc_ray(t_data *cub)
{
	if (cub->player->cam->rayDirX < 0)
	{
		cub->player->cam->r_stepX = -1;
		cub->player->cam->r_sideDistX = (cub->player->posX - cub->player->cam->r_mapX) * cub->player->cam->r_deltaX;
	}
	else
	{
		cub->player->cam->r_stepX = 1;
		cub->player->cam->r_sideDistX = (cub->player->cam->r_mapX + 1.0 - cub->player->posX) * cub->player->cam->r_deltaX;
	}
	if (cub->player->cam->rayDirY < 0)
	{
		cub->player->cam->r_stepY = -1;
		cub->player->cam->r_sideDistY = (cub->player->posY - cub->player->cam->r_mapY) * cub->player->cam->r_deltaY;
	}
	else
	{
		cub->player->cam->r_stepY = 1;
		cub->player->cam->r_sideDistY = (cub->player->cam->r_mapY + 1.0 - cub->player->posY) * cub->player->cam->r_deltaY;
	}
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


int side_calc_ray_bonus(t_data *cub)
{
	int hit;
	int side;

	side = 0;
	hit = 0;
	if (cub->map[(int)cub->player->posY][(int)cub->player->posX] == 'D')
		hit = distance_doors_within_cam(cub, &side);
	while (hit == 0)
	{
		if (fabs(cub->player->cam->r_sideDistX) < fabs(cub->player->cam->r_sideDistY))
		{
			cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
			cub->player->cam->r_mapX += cub->player->cam->r_stepX;
			side = 1;
		}
		else
		{
			cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
			cub->player->cam->r_mapY += cub->player->cam->r_stepY;
			side = 0;
		}
		if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] > '0')
			hit = distance_doors_cam(cub, &side);
	}
	return (side);
}
int distance_doors_cam(t_data *cub, int *side)
{
int door_num;
	double mid_distX;
	double mid_distY;

	if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] == '1')
		return (1);
	if (cub->map[cub->player->cam->r_mapY][cub->player->cam->r_mapX] == 'D')
	{
		door_num = search_door(cub, (double)cub->player->cam->r_mapX, (double)cub->player->cam->r_mapY);
		if (cub->doors[door_num].open == true)
			return (0);
		if (cub->doors[door_num].orientation == 1)
		{
			if (cub->player->cam->r_stepX == -1)
				mid_distX = (cub->player->posX - (cub->player->cam->r_mapX + 0.5 - cub->doors[door_num].position)) * cub->player->cam->r_deltaX;
			else
				mid_distX = ((cub->player->cam->r_mapX + 0.5 - cub->doors[door_num].position) - cub->player->posX) * cub->player->cam->r_deltaX;
			if (fabs(mid_distX) < fabs(cub->player->cam->r_sideDistY))
			{
				cub->player->cam->r_sideDistX = mid_distX;
				*side = 11;
			}
			else
			{
				cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
				cub->player->cam->r_mapY += cub->player->cam->r_stepY;
				*side = 0;
			}
		}
		else if (cub->doors[door_num].orientation == 0)
		{
			if (cub->player->cam->r_stepY == -1)
				mid_distY = (cub->player->posY - (cub->player->cam->r_mapY + 0.5 - cub->doors[door_num].position)) * cub->player->cam->r_deltaY;
			else
				mid_distY = ((cub->player->cam->r_mapY + 0.5 - cub->doors[door_num].position) - cub->player->posY) * cub->player->cam->r_deltaY;
			if (fabs(mid_distY) < fabs(cub->player->cam->r_sideDistX))
			{
				cub->player->cam->r_sideDistY = mid_distY;
				*side = 10;
			}
			else
			{
				cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
				cub->player->cam->r_mapX += cub->player->cam->r_stepX;
				*side = 1;
			}
		}
	}
	return 1;
}

int distance_doors_within_cam(t_data *cub, int *side)
{
	int		door_num;
	double mid_dist;
	
	door_num = search_door(cub, cub->player->posX, cub->player->posY);
	update_door_position(&(cub->doors[door_num]));
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
	{
		if (cub->player->cam->r_stepX == -1)
			mid_dist = (cub->player->posX - (cub->player->cam->r_mapX + 0.5)) * cub->player->cam->r_deltaX;
		else
			mid_dist = ((cub->player->cam->r_mapX + 0.5) - cub->player->posX) * cub->player->cam->r_deltaX;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->cam->r_sideDistY))
		{
			cub->player->cam->r_sideDistX = mid_dist;
			*side = 11;
		}
		else
		{
			cub->player->cam->r_sideDistY += cub->player->cam->r_deltaY;
			cub->player->cam->r_mapY += cub->player->cam->r_stepY;
			*side = 0;
		}
	}
	else if(cub->doors[door_num].orientation == 0)
	{
		if (cub->player->cam->r_stepY == -1)
			mid_dist = (cub->player->posY - (cub->player->cam->r_mapY + 0.5)) * cub->player->cam->r_deltaY;
		else
			mid_dist = ((cub->player->cam->r_mapY + 0.5) - cub->player->posY) * cub->player->cam->r_deltaY;
		if (mid_dist < 0)
			return (0);
		if (fabs(mid_dist) < fabs(cub->player->cam->r_sideDistX))
		{
			cub->player->cam->r_sideDistY = mid_dist;
			*side = 10;
		}
		else
		{
			cub->player->cam->r_sideDistX += cub->player->cam->r_deltaX;
			cub->player->cam->r_mapX += cub->player->cam->r_stepX;
			*side = 1;
		}
	}
	return (1);
}



int		line_display(t_data *cub, int x, double wallDist, int side)
{
	t_castInfo line_prop;
	
	line_prop.x = x;
	line_prop.line_height = WIN_H / wallDist;
	line_prop.yStart = (int)(-line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yStart < 0)
		line_prop.yStart = 0;
    line_prop.yEnd = (int)(line_prop.line_height / 2 + WIN_H / 2);
    if(line_prop.yEnd >= WIN_H)
		line_prop.yEnd = WIN_H - 1;
	line_prop.wallX = wallX_calculator(cub, wallDist, side);
	line_maker(cub, line_prop, side);
	return(1);
}

int wallX_calculator(t_data *cub, double wallDist, int side)
{
	double wall_pos;
	int wallX;

	if(side == 0 || side == 10)
		wall_pos = (cub->player->posX + (wallDist) * cub->player->cam->rayDirX);
	else
		wall_pos = cub->player->posY + (wallDist) * cub->player->cam->rayDirY;
	wall_pos-=(double)((int) wall_pos);
	wallX = (int)(wall_pos * (double)(cub->texNorth.width));
	return(wallX);
}

int	line_maker(t_data *cub, t_castInfo line_prop, int side)
{
	
	if (side == 1)
	{
		if (cub->player->cam->rayDirX > 0)
			liner(cub, line_prop, cub->texEast);
		else
			liner(cub, line_prop, cub->texWest);
	}
	else if (side == 0)
	{
		if (cub->player->cam->rayDirY < 0)
			liner(cub, line_prop, cub->texNorth);
		else
			liner(cub, line_prop, cub->texSouth);	
	}
	else
		liner(cub, line_prop, cub->door);
	return(1);
}

void	liner(t_data *cub, t_castInfo line_prop, t_img tex)
{
	int color;
	double step;
	int texY;
	int pos;
	double texPos;
	
	step = 1.0 * tex.height / line_prop.line_height;
	pos = line_prop.yStart;
	texPos = (line_prop.yStart - WIN_H / 2 + line_prop.line_height / 2) * step;
	while (pos <= line_prop.yEnd)
	{
		texY = (int)texPos & (tex.height - 1);
		texPos += step;
		color = *((int *)(tex.data + (texY * tex.line_length + line_prop.wallX * (cub->texNorth.bits_per_pixel / 8))));
		pixel_put(cub, line_prop.x, pos, color);
		pos++;
	}
}
