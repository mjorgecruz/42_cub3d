/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 10:56:38 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		minimaper(t_data *cub);
void	map_drawing(t_data *cub, int map_scale);
void	render_direction(t_data *cub);
void	hit_point_vertical(t_data *cub);
void	hit_point_horizontal(t_data *cub);

int	minimaper(t_data *cub)
{
	int	map_scale;

	map_scale = 20;
	map_drawing(cub, map_scale);
	render_point_player(cub, (int)(cub->player->posx * map_scale), \
			(int)(cub->player->posy * map_scale));
	render_direction(cub);
	return (1);
}

void	map_drawing(t_data *cub, int map_scale)
{
	double	x;
	double	y;

	y = 0;
	x = 0;
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

void	render_direction(t_data *cub)
{
	double	ang;
	int		side;

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
		bresenham(cub, cub->player->pov->hitx, cub->player->pov->hity);
		ang += 0.05;
	}
}

void	hit_point_vertical(t_data *cub)
{
	if (cub->player->pov->stepx == -1)
	{
		cub->player->pov->hitx = cub->player->pov->mapx + 1;
		cub->player->pov->hity = cub->player->posy + \
			(cub->player->pov->sidedistx - cub->player->pov->deltax) * \
			cub->player->pov->diry;
	}
	else
	{
		cub->player->pov->hitx = cub->player->pov->mapx;
		cub->player->pov->hity = cub->player->posy + \
			(cub->player->pov->sidedistx - cub->player->pov->deltax) * \
			cub->player->pov->diry;
	}
}

void	hit_point_horizontal(t_data *cub)
{
	if (cub->player->pov->stepy == -1)
	{
		cub->player->pov->hitx = cub->player->posx + \
			(cub->player->pov->sidedisty - cub->player->pov->deltay) * \
			cub->player->pov->dirx;
		cub->player->pov->hity = cub->player->pov->mapy + 1;
	}
	else
	{
		cub->player->pov->hitx = cub->player->posx + \
			(cub->player->pov->sidedisty - \
			cub->player->pov->deltay) * cub->player->pov->dirx;
		cub->player->pov->hity = cub->player->pov->mapy;
	}
}
