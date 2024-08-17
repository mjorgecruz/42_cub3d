/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 11:08:42 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculus_display(t_data *cub, double x);
void	display(t_data *cub);
void	delta_calc_ray(t_data *cub);
void	step_calc_ray(t_data *cub);

void	calculus_display(t_data *cub, double x)
{
	cub->player->cam->camerax = (2 * x / (double) WIN_W) - 1;
	cub->player->cam->raydirx = cub->player->pov->dirx + \
		cub->player->cam->planex * cub->player->cam->camerax;
	cub->player->cam->raydiry = cub->player->pov->diry + \
		cub->player->cam->planey * cub->player->cam->camerax;
	delta_calc_ray(cub);
	step_calc_ray(cub);
}

void	display(t_data *cub)
{
	double	x;
	int		side;
	double	walldist;

	x = 1;
	side = 0;
	direction_calc(cub, 0);
	while (x < WIN_W)
	{
		calculus_display(cub, x);
		side = side_calc_ray(cub);
		if (side == 1)
			walldist = fabs((cub->player->cam->r_sidedistx - \
				cub->player->cam->r_deltax));
		else
			walldist = fabs((cub->player->cam->r_sidedisty - \
				cub->player->cam->r_deltay));
		if (walldist < 0.0001)
			walldist = 0.0001;
		line_display(cub, x, walldist, side);
		x++;
	}
}

void	delta_calc_ray(t_data *cub)
{
	cub->player->cam->r_mapx = (int)cub->player->posx;
	cub->player->cam->r_mapy = (int)cub->player->posy;
	if (cub->player->cam->raydirx != 0)
		cub->player->cam->r_deltax = fabs(1 / cub->player->cam->raydirx);
	else
		cub->player->cam->r_deltax = 1e30;
	if (cub->player->cam->raydiry != 0)
		cub->player->cam->r_deltay = fabs(1 / cub->player->cam->raydiry);
	else
		cub->player->cam->r_deltay = 1e30;
}

void	step_calc_ray(t_data *cub)
{
	if (cub->player->cam->raydirx < 0)
	{
		cub->player->cam->r_stepx = -1;
		cub->player->cam->r_sidedistx = (cub->player->posx - \
			cub->player->cam->r_mapx) * cub->player->cam->r_deltax;
	}
	else
	{
		cub->player->cam->r_stepx = 1;
		cub->player->cam->r_sidedistx = (cub->player->cam->r_mapx + 1.0 - \
			cub->player->posx) * cub->player->cam->r_deltax;
	}
	if (cub->player->cam->raydiry < 0)
	{
		cub->player->cam->r_stepy = -1;
		cub->player->cam->r_sidedisty = (cub->player->posy - \
			cub->player->cam->r_mapy) * cub->player->cam->r_deltay;
	}
	else
	{
		cub->player->cam->r_stepy = 1;
		cub->player->cam->r_sidedisty = (cub->player->cam->r_mapy + 1.0 - \
			cub->player->posy) * cub->player->cam->r_deltay;
	}
}
