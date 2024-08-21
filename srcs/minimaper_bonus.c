/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:31 by masoares          #+#    #+#             */
/*   Updated: 2024/08/20 14:09:14 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int		minimaper_bonus(t_data *cub);
void	map_drawing_bonus(t_data *cub, int map_scale);
void	render_direction_bonus(t_data *cub);
void	hit_point_vertical(t_data *cub);
void	hit_point_horizontal(t_data *cub);

int	minimaper_bonus(t_data *cub)
{
	int	map_scale;

	map_scale = 20;
	map_drawing_bonus(cub, map_scale);
	render_point_player(cub, (int)(cub->player->posx * map_scale), \
		(int)(cub->player->posy * map_scale));
	render_direction_bonus(cub);
	return (1);
}

void	map_drawing_bonus(t_data *cub, int map_scale)
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
			else if (cub->map[(int) y][(int) x] == 'D')
				render_rect_door(cub, x, y, map_scale);
			else if (cub->map[(int) y][(int) x] == 'F')
				render_rect_fire(cub, x, y, map_scale);
			x++;
		}
		y++;
	}
}

void	render_direction_bonus(t_data *cub)
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
		else if (side == 0)
			hit_point_horizontal(cub);
		else if (side == 10)
			hit_point_horizontal_door(cub);
		else if (side == 11)
			hit_point_vertical_door(cub);
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
			(cub->player->pov->sidedisty - cub->player->pov->deltay) * \
			cub->player->pov->dirx;
		cub->player->pov->hity = cub->player->pov->mapy;
	}
}
