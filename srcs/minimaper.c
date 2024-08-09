/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/08/09 23:01:01 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIN_W && y < WIN_H && x > 0 && y > 0) 
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	render_point_player(t_data *img, double pos_x, double pos_y)
{
	int     color;

	color = 0xFFFFFF;
	pixel_put(img, (int) pos_x, (int) pos_y, color);
	pixel_put(img, (int) pos_x + 1, (int)pos_y, color);
	pixel_put(img, (int) pos_x - 1, (int) pos_y , color);
	pixel_put(img, (int) pos_x, (int) pos_y + 1, color);
	pixel_put(img, (int) pos_x, (int) pos_y - 1, color);
	
	
	
}

void	render_rect_wall(t_data *img, int pos_x, int pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = pos_x * scale;
	j = pos_y * scale;

	while (i < pos_x * scale + scale - 1)
	{
		j = pos_y * scale;
		while (j < pos_y * scale + scale - 1)
		{
			color = 0x305060;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	render_rect_ground(t_data *img, int pos_x, int pos_y, int scale)
{
	int		i;
	int		j;
	int     color;

	i = pos_x * scale;
	j = pos_y * scale;
	while (i < pos_x * scale + scale)
	{
		j = pos_y * scale;
		while (j < pos_y * scale + scale)
		{
			color = 0x000000;
			pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

int minimaper(t_data *cub)
{
	double		x;
	double		y;
	int 	map[4][4] = {{1, 1, 1, 1},{1, 0, 0, 1}, {1, 0, 'N', 1}, {1, 1, 1, 1}};
	int		map_scale;

	map_scale = 20;
	cub->map_h = 4;
	cub->map_w = 4;
	y = 0;
	x = 0;
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	while (y < cub->map_h)
	{
		x = 0;
		while (x < cub->map_w)
		{
			if (map[(int) x][(int) y] == 1)
				render_rect_wall(cub, x, y, map_scale);
			else if (cub->map[(int) x][(int) y] == 0)
				render_rect_ground(cub, x, y, map_scale);
			else
			{
				render_rect_ground(cub, x, y, map_scale);
				cub->player->posX = x + 0.5;
				cub->player->posY = y + 0.5;
				cub->map[(int) x][(int) y] = 0;
			}
			x++;
		}
		y++;
	}
	render_point_player(cub, (int) (cub->player->posX * map_scale), (int) (cub->player->posY * map_scale));
	render_direction(cub);
	return (1);

}

int	bresenham(t_data *img, double u1, double v1)
{
	double	varu;
	double	varv;
	int		max;
	int		map_scale = 20;
	
	double u;
	double v;
	u = img->player->posX * map_scale;
	v = img->player->posY * map_scale;
	u1 = u1 * map_scale;
	v1 = v1 * map_scale;
	varu =  u1 - u;
	varv = v1 - v;
	max = max_finder(varu, varv);
	varu /= max;
	varv /= max;
	int i = 0;
	
	while (((int)(u - u1) || (int)(v - v1)))
	{
		pixel_put(img, (int) u, (int) v, 0xFFFFFF);
		u += varu;
		v += varv;
		i++;
	}
	return (1);
}

int	bresenham_wall(t_data *img, double x, double x1, double y, double y1)
{
	double	varu;
	double	varv;
	int		max;
	
	varu = x1 - x;
	varv = y1 - y;
	max = max_finder(varu, varv);
	varu /= max;
	varv /= max;
	
	while (((int)(x - x1) || (int)(y - y1)))
	{
		pixel_put(img, (int) x, (int) y, 0xFFFFFF);
		x += varu;
		y += varv;
	}
	return (1);
}

int	max_finder(double varu, double varv)
{
	if (varu < 0)
		varu *= (-1);
	if (varv < 0)
		varv *= (-1);
	if (varu < varv) 
		return (varv);
	else
		return (varu);
}

void render_direction(t_data *cub)
{
	double ang = (-cub->player->fov / 2);
	while (ang <= cub->player->fov / 2)
	{
		double sideDistX; //distance to the next edge in x
		double sideDistY; //distance to the next edge in y
		double deltaX; //distance to progress one unit in y
		double deltaY; //distance to progress one unit in x

		double dirX = cos(cub->player->player_ang + ang);
		double dirY = sin(cub->player->player_ang );
		if (dirX < 0.00001 && dirX > -0.00001)
			dirX = 0;
		if (dirY < 0.00001 && dirY > -0.00001)
			dirY = 0;		

		int stepX;
		int stepY;
		int mapX = (int)cub->player->posX;
		int mapY = (int)cub->player->posY;
		int hit = 0;

			if (dirX != 0)
				deltaX = fabs(1 / dirX); 
			else
				deltaX = 1e30;
			if (dirY != 0)
				deltaY = fabs(1 / dirY);
			else
				deltaY = 1e30;
		if (dirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player->posX - mapX) * deltaX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player->posX) * deltaX;
		}
		if (dirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player->posY - mapY) * deltaY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player->posY) * deltaY;
		}
		int side = 0;
		while (hit == 0)
		{
			if (fabs(sideDistX) < fabs(sideDistY))
			{
				sideDistX += deltaX;
				mapX += stepX;
				side = 1;
			}
			else
			{
				sideDistY += deltaY;
				mapY += stepY;
				side = 0;
			}
			if (cub->map[mapX][mapY] > 0)
				hit = 1;
		}
		double hitX, hitY;
		if (side == 1)
		{
			if (stepX == -1)
			{
				hitX = mapX + 1;
				hitY = cub->player->posY + (sideDistX - deltaX) * dirY;
			}
			else
			{
				hitX = mapX;
				hitY = cub->player->posY + (sideDistX - deltaX) * dirY;
			}
		}
		else
		{
			if (stepY == -1)
			{
				hitX = cub->player->posX + (sideDistY - deltaY) * dirX;
				hitY = mapY + 1;
			}
			else
			{
				hitX = cub->player->posX + (sideDistY - deltaY) * dirX;
				hitY = mapY;
			}
		}
		printf("mapX %d mapY %d\n", mapX, mapY);
		printf("deltaX %f, deltaY %f\n", deltaX, deltaY);
		printf("dirX %f, dirY %f\n", dirX, dirY);
		printf("hitX %f, hitY %f\n", hitX, hitY);
		printf("stepX %d, stepY %d\n", stepX, stepY);
		printf("side %d\n", side);
		bresenham(cub, hitX, hitY);
		ang+=0.05;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}