/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/07/31 09:17:19 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	pixel_put(img, pos_x, pos_y, color);
	pixel_put(img, pos_x + 1, pos_y, color);
	pixel_put(img, pos_x - 1, pos_y , color);
	pixel_put(img, pos_x, pos_y + 1, color);
	pixel_put(img, pos_x, pos_y - 1, color);
	
	
	
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
	render_point_player(cub, x * map_scale, y * map_scale);
	bresenham(cub, cub->player->player_ang);
	bresenham(cub, cub->player->player_ang + (cub->player->fov / 2));
	bresenham(cub, cub->player->player_ang - (cub->player->fov / 2));
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
	return (1);
}

int minimaper_initial(t_data *cub)
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
	
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (map[(int) x][(int) y] == 1)
				render_rect_wall(cub, x, y, map_scale);
			else if (map[(int) x][(int) y] == 0)
				render_rect_ground(cub, x, y, map_scale);
			else
			{
				render_rect_ground(cub, x, y, map_scale);
				render_point_player(cub, x, y);
				cub->player->posX = x + 0.5;
				cub->player->posY = y + 0.5;
			}
			x++;
		}
		y++;
	}
	render_point_player(cub, x * map_scale, y * map_scale);
	bresenham(cub, cub->player->player_ang);
	bresenham(cub, cub->player->player_ang + (cub->player->fov / 2));
	bresenham(cub, cub->player->player_ang - (cub->player->fov / 2));
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
	return (1);
}

int	bresenham(t_data *img, double ang)
{
	double	varu;
	double	varv;
	int		max;
	int		map_scale = 10;
	
	double u;
	double v;
	double u1;
	double v1;
	
	u = img->player->posX * map_scale;
	v = img->player->posY * map_scale;
	u1 = u + 1*(cos(ang) * map_scale);
	v1 = v + 1*(sin(ang) * map_scale);
	varu = u1 - u;
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