/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/08/07 02:09:06 by masoares         ###   ########.fr       */
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
			else
				render_rect_ground(cub, x, y, map_scale);
			x++;
		}
		y++;
	}
	render_point_player(cub, (int) (cub->player->posX * map_scale), (int) (cub->player->posY * map_scale));
	render_direction(cub);
	return (1);

}

int minimaper_initial(t_data *cub)
{
	double		x;
	double		y;
	int		map_scale;

	map_scale = 20;
	y = 0;
	x = 0;
	
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (cub->map[(int) x][(int) y] == 1)
				render_rect_wall(cub, x, y, map_scale);
			else if (cub->map[(int) x][(int) y] == 0)
				render_rect_ground(cub, x, y, map_scale);
			else
			{
				render_rect_ground(cub, x, y, map_scale);
				cub->player->posX = x + 0.5;
				cub->player->posY = y + 0.5;
			}
			x++;
		}
		y++;
	}
	render_point_player(cub, cub->player->posX * map_scale, cub->player->posY * map_scale);
	bresenham(cub, cub->player->posX + cos(cub->player->player_ang), cub->player->posY + sin(cub->player->player_ang));
	double ang = (-cub->player->fov / 2);
	while (ang <= cub->player->fov / 2)
	{
		bresenham(cub,cub->player->posX + cos(cub->player->player_ang + ang), cub->player->posY + sin(cub->player->player_ang + ang));
		ang+=0.05;
	}	
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
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
	// double ang = (-cub->player->fov / 2);
	// while (ang <= cub->player->fov / 2)
	// {
		double sideDistX; //distance to the next edge in x
    	double sideDistY; //distance to the next edge in y
		double deltaDistX; //distance to progress one unit in x
    	double deltaDistY; //distance to progress one unit in y

		double rayDirX = cos(cub->player->player_ang);
    	double rayDirY = sin(cub->player->player_ang);
		if (rayDirX < 0.00001 && rayDirX > -0.00001)
			rayDirX = 0;
		if (rayDirY < 0.00001 && rayDirY > -0.00001)
			rayDirY = 0;		

		int stepX;
    	int stepY;
		double mapX = cub->player->posX;
		double mapY = cub->player->posY;
		int hit = 0;

		while (hit == 0)
		{
			if (rayDirX != 0)
				deltaDistX = rayDirY / rayDirX; 
			else
				deltaDistX = 1e30;
			if (rayDirY != 0)
				deltaDistY = rayDirX / rayDirY;
			else
				deltaDistY = 1e30;
	
			if (rayDirX < 0)
    		{
    		    stepX = -1;
    		    sideDistX = (int)mapX + 1 + deltaDistX - mapX;
    		}
    		else
    		{
    		    stepX = 1;
    		    sideDistX = (int)mapX + deltaDistX -mapX;
    		}
    		if (rayDirY < 0)
    		{
    	    	stepY = -1;
    	    	sideDistY = 1 - mapY+ (int)mapY + deltaDistY;
    		}
    		else
    		{
    		    stepY = 1;
    		    sideDistY = (int)mapY - mapY + deltaDistY;
			}
			if (fabs(sideDistX) > fabs(sideDistY))
			{
				mapX += (sideDistX * rayDirX);
				mapY += stepY;
			}
			else
			{
				mapX += stepX;
				mapY += sideDistY * rayDirY;
			}
			if (cub->map[(int)mapX][(int)mapY] > 0)
				hit = 1;
    	}
		printf("mapX %f mapy %f\n", mapX, mapY);
		bresenham(cub, mapX, mapY);
	// 	ang+=0.05;
	// }
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}