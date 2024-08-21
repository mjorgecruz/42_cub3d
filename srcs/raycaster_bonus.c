/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:59:31 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	display_bonus(t_data *cub);
void	camera_calculations(t_data *cub, int x);
void	wall_displayer(t_data *cub, int x);
void	sprite_displayer(t_data *cub, int x);

void	display_bonus(t_data *cub)
{
	double	x;

	x = 1;
	direction_calc(cub, 0);
	while (x < WIN_W)
	{
		camera_calculations(cub, x);
		wall_displayer(cub, x);
		x++;
	}
	x = 1;
	while (x < WIN_W)
	{
		camera_calculations(cub, x);
		sprite_displayer(cub, x);
		x++;
	}
}

void	camera_calculations(t_data *cub, int x)
{
	cub->player->cam->camerax = (2 * x / (double) WIN_W) - 1;
	cub->player->cam->raydirx = cub->player->pov->dirx + \
		cub->player->cam->planex * cub->player->cam->camerax;
	cub->player->cam->raydiry = cub->player->pov->diry + \
		cub->player->cam->planey * cub->player->cam->camerax;
	delta_calc_ray(cub);
	step_calc_ray(cub);
}

void	wall_displayer(t_data *cub, int x)
{
	int		side;
	double	walldist;

	walldist = 0.0;
	side = side_calc_ray(cub);
	if (side == 1)
		walldist = fabs((cub->player->cam->r_sidedistx - \
			cub->player->cam->r_deltax));
	else if (side == 0)
		walldist = fabs((cub->player->cam->r_sidedisty - \
			cub->player->cam->r_deltay));
	if (walldist < 0.0001)
		walldist = 0.0001;
	if (side == 0 || side == 1)
		line_display(cub, x, walldist, side);
}

void	sprite_displayer(t_data *cub, int x)
{
	int		side;
	double	walldist;

	walldist = 0.0;
	side = side_calc_ray_bonus(cub, x);
	if (side == 10)
		walldist = fabs((cub->player->cam->r_sidedisty));
	else if (side == 11)
		walldist = fabs((cub->player->cam->r_sidedistx));
	else if (side == 20)
		walldist = fabs((cub->player->cam->r_sidedisty));
	if (walldist < 0.0001)
		walldist = 0.0001;
	if (side == 10 || side == 11)
		line_display_door(cub, x, walldist, side);
	else if (side == 20)
		line_display_fire(cub, x, walldist, side);
}
